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

	lManager->setRandom(qEnvironmentObj);

	// add the gui thing here

	VertexShape* player1QBar = new VertexShape();

	player1QBar->graphics = graphics;
	D3DXCreateMeshFVF(12, 24, D3DXMESH_MANAGED, CUSTOMFVF, graphics->get3Ddevice(), &player1QBar->meshPtr);
	player1QBar->color = D3DXVECTOR3(255, 255, 255);
	player1QBar->meshPtr->LockVertexBuffer(0, (void**)&player1QBar->vertices);
	player1QBar->vertices[0] = { -1.0f / ASPECT_RATIO / 2, -1.0f / 2, -1.0f / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(player1QBar->color.x), (int)(player1QBar->color.y), (int)(player1QBar->color.z)) };
	player1QBar->vertices[1] = { -1.0f / ASPECT_RATIO / 2, +1.0f / 2, -1.0f / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(player1QBar->color.x), (int)(player1QBar->color.y), (int)(player1QBar->color.z)) };
	player1QBar->vertices[2] = { +1.0f / ASPECT_RATIO / 2, +1.0f / 2, -1.0f / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(player1QBar->color.x), (int)(player1QBar->color.y), (int)(player1QBar->color.z)) };
	player1QBar->vertices[3] = { +1.0f / ASPECT_RATIO / 2, -1.0f / 2, -1.0f / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(player1QBar->color.x), (int)(player1QBar->color.y), (int)(player1QBar->color.z)) };
	player1QBar->vertices[4] = { -1.0f / ASPECT_RATIO / 2, -1.0f / 2, +1.0f / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(player1QBar->color.x), (int)(player1QBar->color.y), (int)(player1QBar->color.z)) };
	player1QBar->vertices[5] = { -1.0f / ASPECT_RATIO / 2, +1.0f / 2, +1.0f / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(player1QBar->color.x), (int)(player1QBar->color.y), (int)(player1QBar->color.z)) };
	player1QBar->vertices[6] = { +1.0f / ASPECT_RATIO / 2, +1.0f / 2, +1.0f / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(player1QBar->color.x), (int)(player1QBar->color.y), (int)(player1QBar->color.z)) };
	player1QBar->vertices[7] = { +1.0f / ASPECT_RATIO / 2, -1.0f / 2, +1.0f / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(player1QBar->color.x), (int)(player1QBar->color.y), (int)(player1QBar->color.z)) };
	player1QBar->meshPtr->UnlockVertexBuffer();
	player1QBar->vertexCount = 8;
	player1QBar->meshPtr->LockIndexBuffer(0, (void**)&player1QBar->indices);
	player1QBar->indices[0] = 0; player1QBar->indices[1] = 1; player1QBar->indices[2] = 2;
	player1QBar->indices[3] = 0; player1QBar->indices[4] = 2; player1QBar->indices[5] = 3;
	player1QBar->indices[6] = 4; player1QBar->indices[7] = 6; player1QBar->indices[8] = 5;
	player1QBar->indices[9] = 4; player1QBar->indices[10] = 7; player1QBar->indices[11] = 6;
	player1QBar->indices[12] = 4; player1QBar->indices[13] = 5; player1QBar->indices[14] = 1;
	player1QBar->indices[15] = 4; player1QBar->indices[16] = 1; player1QBar->indices[17] = 0;
	player1QBar->indices[18] = 3; player1QBar->indices[19] = 2; player1QBar->indices[20] = 6;
	player1QBar->indices[21] = 3; player1QBar->indices[22] = 6; player1QBar->indices[23] = 7;
	player1QBar->indices[24] = 1; player1QBar->indices[25] = 5; player1QBar->indices[26] = 6;
	player1QBar->indices[27] = 1; player1QBar->indices[28] = 6; player1QBar->indices[29] = 2;
	player1QBar->indices[30] = 4; player1QBar->indices[31] = 0; player1QBar->indices[32] = 3;
	player1QBar->indices[33] = 4; player1QBar->indices[34] = 3; player1QBar->indices[35] = 7;
	player1QBar->meshPtr->UnlockIndexBuffer();
	player1QBar->indicesCount = 36;
	player1QBar->visible = true;
	player1QBar->alive = true;
	// hardcode this first
	player1QBar->pos.x = -5;
	player1QBar->pos.y = -3;
	player1QBar->pos.z = 10;
	player1QBar->scale.x = 5.0f;
	player1QBar->scale.y = 1.0f;
	player1QBar->scale.z = 1.0f;

	qGUIObj.push_back(player1QBar);
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

	graphics->camera->update(*deltaTime);

	setNextStateByInput(stateNS::REVERT, controls.at(CONTROL_ESC));

	for (int i = 0; i < qGUIObj.size(); i++) {
		qGUIObj[i]->scale.x -= (*deltaTime); 
	}
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


	for (int i = 0; i < qGUIObj.size(); i++) {
		LPDIRECT3DVERTEXBUFFER9 vBuffer;
		LPDIRECT3DINDEXBUFFER9 iBuffer;

		D3DXMATRIX scaleMat;
		D3DXMATRIX transMat;

		qGUIObj[i]->meshPtr->GetVertexBuffer(&vBuffer);
		qGUIObj[i]->meshPtr->GetIndexBuffer(&iBuffer);
		qGUIObj[i]->graphics->get3Ddevice()->SetStreamSource(0, vBuffer, 0, sizeof(LVertex));
		qGUIObj[i]->graphics->get3Ddevice()->SetIndices(iBuffer);
		D3DXMatrixScaling(&scaleMat, qGUIObj[i]->scale.x, qGUIObj[i]->scale.y, qGUIObj[i]->scale.z);
		D3DXMatrixTranslation(&transMat, qGUIObj[i]->pos.x, qGUIObj[i]->pos.y, qGUIObj[i]->pos.z);
		worldMatrix = scaleMat * transMat;
		qGUIObj[i]->graphics->get3Ddevice()->SetTransform(D3DTS_WORLD, &worldMatrix);
		qGUIObj[i]->meshPtr->DrawSubset(0);
	}
}
