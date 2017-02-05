#include "quicky.h"
#include "src/QLine.h"

Obstacle* o1 = new Obstacle(D3DXVECTOR3(0, 10, 20 - 0.5), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 0, 255));
Obstacle* o2 = new Obstacle(D3DXVECTOR3(-5, 0, 20 - 0.5), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 0, 255));
Obstacle* o3 = new Obstacle(D3DXVECTOR3(0, -10, 20 - 0.5), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 0, 255));
Obstacle* o4 = new Obstacle(D3DXVECTOR3(5, 0, 20 - 0.5), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 0, 255));
Obstacle* o5 = new Obstacle(D3DXVECTOR3(5, 0, 20 - 0.5), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 0, 255));
Obstacle* o6 = new Obstacle(D3DXVECTOR3(5, 0, 20 - 0.5), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 0, 255));

Player* sqr1 = new Player(D3DXVECTOR3(0, 0, 20 - 1), D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 255, 255));
Player* sqr2 = new Player(D3DXVECTOR3(10, 10, 20 - 1), D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 240, 240));

quicky::quicky() {
	lManager = new LevelManager();
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
	qObstacles.push_back(o5);
	qObstacles.push_back(o6);

	qPlayer.push_back(sqr1);
	qPlayer.push_back(sqr2);

	// Initialize menu
	Menu* menu = new Menu();
	menu->initialize(this->getGraphics(), this->getInput());

	// Start game state in menu
	gameState.push(menu);

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

	// parse obstacles details
	FILE* obsFile = fopen("resource\\data\\obstacles.json", "rb");
	char obsBuffer[512];
	rapidjson::FileReadStream obsStream(obsFile, obsBuffer, sizeof(obsBuffer));
	obstacleDoc.ParseStream(obsStream);
	printf("%s\n", obstacleDoc["test_string"].GetString());
	fclose(obsFile);

	for (int i = 0; i < qObstacles.size(); i++) {
		Obstacle* tempObs = (Obstacle*)qObstacles[i];
		tempObs->assign(obstacleDoc);
	}

	lManager->setRandomLevel(qObstacles);

	sqr1->assignControl(controlDoc);
	sqr2->assignControl(controlDoc);
	menu->initControls(controlDoc);
}

void quicky::update() {

	gameState.top()->update();
	lManager->update(deltaTime, qObstacles);

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

	D3DXVECTOR3 out1;
	D3DXVECTOR2 out2;
	graphics->camera->pointOnScreen(out1, sqr1->pos, worldMat);
	out2 = D3DXVECTOR2(out1.x, out1.y);
	graphics->camera->pointInWorld(out1, out2, 20);
	printf("POS %.2f, %.2f | %.2f, %.2f\n", out1.x, out1.y, sqr1->pos.x, sqr1->pos.y);

	graphics->camera->pitch(-1.0 * deltaTime);
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

	gameState.top()->render();
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
