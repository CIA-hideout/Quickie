#include "quicky.h"
#include "src/QLine.h"

Obstacle* o1 = new Obstacle(D3DXVECTOR3(0, 10, 20 - 0.5), D3DXVECTOR3(10, 1.5, 0.5), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 0, 255));
Obstacle* o2 = new Obstacle(D3DXVECTOR3(-5, 0, 20 - 0.5), D3DXVECTOR3(1.5, 10, 0.5), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 0, 255));
Obstacle* o3 = new Obstacle(D3DXVECTOR3(0, -10, 20 - 0.5), D3DXVECTOR3(10, 1.5, 0.5), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 0, 255));
Obstacle* o4 = new Obstacle(D3DXVECTOR3(5, 0, 20 - 0.5), D3DXVECTOR3(1.5, 10, 0.5), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 0, 255));

Player* sqr1 = new Player(D3DXVECTOR3(0, 0, 20 - 1), D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 255, 255));
Player* sqr2 = new Player(D3DXVECTOR3(10, 10, 20 - 1), D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 240, 240));

quicky::quicky() {

}

quicky::~quicky() {

}

void quicky::initialize(HWND hWnd) {

	Game::initialize(hWnd);

	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);

	qObstacles.push_back(o1);
	qObstacles.push_back(o2);
	qObstacles.push_back(o3);
	qObstacles.push_back(o4);

	qPlayer.push_back(sqr1);
	qPlayer.push_back(sqr2);

	// GUI initialization
	gui = new GUI();

	if (!gui->initialize(this))
		throw(GameError(gameErrorNS::FATAL_ERROR, "FAIL TO INITIALIZE GUI"));

	// parse player control
	FILE* controlFile = fopen("resource\\data\\control.json", "rb");
	char controlBuffer[512];
	rapidjson::FileReadStream is(controlFile, controlBuffer, sizeof(controlBuffer));
	controlDoc.ParseStream(is);
	printf("%s\n", controlDoc["test_string"].GetString());
	fclose(controlFile);

	for (int i = 0; i < qObstacles.size(); i++) {
		qObstacles[i]->init(this);
	}

	for (int i = 0; i < qPlayer.size(); i++) {
		Player* temp = (Player*)qPlayer[i];
		temp->init(this);
		temp->assignControl(controlDoc);
	}
}

void quicky::update() {
	for (int i = 0; i < qObstacles.size(); i++) {
		if (qObstacles[i]->objectType == OT_QL) {
			QLine* temp = (QLine*)qObstacles[i];
			temp->update(deltaTime, qObstacles);
		}
		else if (qObstacles[i]->objectType == OT_OBS) {
			Obstacle* temp = (Obstacle*)qObstacles[i];
			temp->update(deltaTime);
		}
	}

	for (int i = 0; i < qPlayer.size(); i++) {
		Player* temp = (Player*)qPlayer[i];
		temp->update(deltaTime, qObstacles);
	}

	// push all temp stuff into respective vectors

	gui->update();
}

void quicky::ai() {

}

void quicky::collisions() {

}

void quicky::render() {

	for (int i = 0; i < qObstacles.size(); i++) {
		qObstacles[i]->draw(worldMat);
	}

	for (int i = 0; i < qPlayer.size(); i++) {
		Player* temp = (Player*)qPlayer[i];
		temp->draw(worldMat);
	}

	gui->render();
}

void quicky::releaseAll() {
	FreeConsole();
}

void quicky::resetAll() {

}

void quicky::updateKeyboard() {

}

void quicky::keyPress(int key) {

}

void quicky::keyRelease(int key) {

}