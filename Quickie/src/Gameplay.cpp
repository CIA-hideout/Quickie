#include "Gameplay.h"

Gameplay::Gameplay()
{
	D3DXMatrixIdentity(&worldMatrix);

	lManager = new LevelManager();

	o1 = new Obstacle(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1), COLOR_PURPLE);
	o2 = new Obstacle(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1), COLOR_PURPLE);
	o3 = new Obstacle(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1), COLOR_PURPLE);
	o4 = new Obstacle(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1), COLOR_PURPLE);
	o5 = new Obstacle(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1), COLOR_PURPLE);
	o6 = new Obstacle(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1), COLOR_PURPLE);

	w1 = new Wall(D3DXVECTOR3(0, 22, 19.5), DIMENSION_HORIZONTAL_WALL, D3DXVECTOR3(1, 1, 1), COLOR_RED);		// - up
	w2 = new Wall(D3DXVECTOR3(0, -22, 19.5), DIMENSION_HORIZONTAL_WALL, D3DXVECTOR3(1, 1, 1), COLOR_RED);	// - down
	w3 = new Wall(D3DXVECTOR3(-21, 0, 19.5), DIMENSION_VERTICAL_WALL, D3DXVECTOR3(1, 1, 1), COLOR_RED);		// | left
	w4 = new Wall(D3DXVECTOR3(21, 0, 19.5), DIMENSION_VERTICAL_WALL, D3DXVECTOR3(1, 1, 1), COLOR_RED);		// | right
	
	sqr1 = new Player(D3DXVECTOR3(0, 0, 20 - 1), D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(240, 240, 0));
	sqr2 = new Player(D3DXVECTOR3(10, 10, 20 - 1), D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 240, 240));

}

Gameplay::~Gameplay()
{

}

void Gameplay::initialize(Graphics* g, Input* i, Audio* a, rapidjson::Document& controlsDoc, float* dT)
{
	State::initialize(g, i, a, controlsDoc);

	deltaTime = dT;
	lManager->init(audio);

	qEnvironmentObj.push_back(o1);
	qEnvironmentObj.push_back(o2);
	qEnvironmentObj.push_back(o3);
	qEnvironmentObj.push_back(o4);
	qEnvironmentObj.push_back(o5);
	qEnvironmentObj.push_back(o6);

	qEnvironmentObj.push_back(w1);
	qEnvironmentObj.push_back(w2);
	qEnvironmentObj.push_back(w3);
	qEnvironmentObj.push_back(w4);
	
	qPlayer.push_back(sqr1);
	qPlayer.push_back(sqr2);

	// parse obstacles details
	FILE* obsFile = fopen("resource\\data\\obstacles.json", "rb");
	char obsBuffer[512];
	rapidjson::FileReadStream obsStream(obsFile, obsBuffer, sizeof(obsBuffer));
	obstacleDoc.ParseStream(obsStream);
	printf("%s\n", obstacleDoc["test_string"].GetString());
	fclose(obsFile);

	for (int i = 0; i < qEnvironmentObj.size(); i++) {
		Obstacle* temp = (Obstacle*)qEnvironmentObj[i];
		temp->init(this->audio, this->graphics);
			
		if (qEnvironmentObj[i]->objectType == OBJECT_TYPE_OBSTACLE)
				temp->assignPosition(obstacleDoc, i);
	}

	for (int i = 0; i < qPlayer.size(); i++) {
		Player* temp = (Player*)qPlayer[i];
		temp->init(this->graphics, this->input);
		temp->assignControl(controlsDoc, i);
	}

	lManager->setRandom(qEnvironmentObj, qPlayer);
}

void Gameplay::update()
{
	for (int i = 0; i < qEnvironmentObj.size(); i++) {
		if (qEnvironmentObj[i]->objectType == OBJECT_TYPE_QLINE) {
			QLine* temp = (QLine*)qEnvironmentObj[i];
			temp->update(*deltaTime, qEnvironmentObj);
		}
		else if (qEnvironmentObj[i]->objectType == OBJECT_TYPE_OBSTACLE) {
			Obstacle* temp = (Obstacle*)qEnvironmentObj[i];
			temp->update(*deltaTime, qPlayer);
		}
	}

	for (int i = 0; i < qPlayer.size(); i++) {
		Player* temp = (Player*)qPlayer[i];
		temp->update(*deltaTime, qEnvironmentObj);
	}

	lManager->update(*deltaTime, qEnvironmentObj, qPlayer);

	graphics->camera->update(*deltaTime);

	setNextStateByInput(stateNS::REVERT, controls.at(CONTROL_ESC));
}

void Gameplay::render()
{
	for (int i = 0; i < qEnvironmentObj.size(); i++) {
		qEnvironmentObj[i]->draw(worldMatrix);
	}

	for (int i = 0; i < qPlayer.size(); i++) {
		Player* temp = (Player*)qPlayer[i];
		temp->draw(worldMatrix);
	}
}
