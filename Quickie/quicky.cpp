#include "quicky.h"
#include "src/QLine.h"

Obstacle* o1 = new Obstacle(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1), COLOR_PURPLE);
Obstacle* o2 = new Obstacle(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1), COLOR_PURPLE);
Obstacle* o3 = new Obstacle(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1), COLOR_PURPLE);
Obstacle* o4 = new Obstacle(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1), COLOR_PURPLE);
Obstacle* o5 = new Obstacle(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1), COLOR_PURPLE);
Obstacle* o6 = new Obstacle(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1), COLOR_PURPLE);

Player* sqr1 = new Player(D3DXVECTOR3(0, 0, 20 - 1), D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 255, 255));
Player* sqr2 = new Player(D3DXVECTOR3(10, 10, 20 - 1), D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 240, 240));

quicky::quicky() {
	lManager = new LevelManager();
}

quicky::~quicky() {

}

void quicky::initialize(HWND hWnd) {

	Game::initialize(hWnd);
	lManager->init(audio);

	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);

	qEnvironmentObj.push_back(o1);
	qEnvironmentObj.push_back(o2);
	qEnvironmentObj.push_back(o3);
	qEnvironmentObj.push_back(o4);
	qEnvironmentObj.push_back(o5);
	qEnvironmentObj.push_back(o6);

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

	for (int i = 0; i < qEnvironmentObj.size(); i++) {
		Obstacle* temp = (Obstacle*)qEnvironmentObj[i];
	  temp->init(this->audio, this->graphics);
	}

	for (int i = 0; i < qPlayer.size(); i++) {
		Player* temp = (Player*)qPlayer[i];
		temp->init(this->graphics, this->input);
		temp->assignControl(controlDoc);
	}

	// parse obstacles details
	FILE* obsFile = fopen("resource\\data\\obstacles.json", "rb");
	char obsBuffer[512];
	rapidjson::FileReadStream obsStream(obsFile, obsBuffer, sizeof(obsBuffer));
	obstacleDoc.ParseStream(obsStream);
	printf("%s\n", obstacleDoc["test_string"].GetString());
	fclose(obsFile);

	for (int i = 0; i < qEnvironmentObj.size(); i++) {
		Obstacle* tempObs = (Obstacle*)qEnvironmentObj[i];
		tempObs->assign(obstacleDoc);
	}

	lManager->setRandomLevel(qEnvironmentObj);

	sqr1->assignControl(controlDoc);
	sqr2->assignControl(controlDoc);
	menu->initControls(controlDoc);

}

void quicky::update() {

	gameState.top()->update();
	lManager->update(deltaTime, qEnvironmentObj);

	if (gameState.top()->getNextState() != nullptr)
	{
		stateNS::NextState pState = *gameState.top()->getNextState();
		gameState.top()->clearNextState();

		switch (pState)
		{
		case stateNS::INSTRUCTIONS:
		{
									  Instructions* i = new Instructions();

									  i->initialize(graphics, input);
									  gameState.push(i);
		}
			break;

	if (gameState.top()->getNextState() != nullptr)
	{
		printf("NEXT STATE\n");
		stateNS::NextState pState = *gameState.top()->getNextState();
		gameState.top()->clearNextState();

		switch (pState)
		{
		case stateNS::INSTRUCTIONS:
		{
									  Instructions* i = new Instructions();

									  i->initialize(graphics, input);
									  gameState.push(i);
		}
			break;

		case stateNS::GAMEPLAY:
			break;

		case stateNS::REVERT:
			gameState.pop();
			break;
		}
	}

	for (int i = 0; i < qEnvironmentObj.size(); i++) {
		if (qEnvironmentObj[i]->objectType == OBJECT_TYPE_QLINE) {
			QLine* temp = (QLine*)qEnvironmentObj[i];
			temp->update(deltaTime, qEnvironmentObj);
		}
		else if (qEnvironmentObj[i]->objectType == OBJECT_TYPE_OBSTACLE) {
			Obstacle* temp = (Obstacle*)qEnvironmentObj[i];
			temp->update(deltaTime, qPlayer);
		}
	}

	for (int i = 0; i < qPlayer.size(); i++) {
		Player* temp = (Player*)qPlayer[i];
		temp->update(deltaTime, qEnvironmentObj);
	}
	
	graphics->camera->update(deltaTime);
}

void quicky::ai() {

}

void quicky::collisions() {

}

void quicky::render() {

	for (int i = 0; i < qEnvironmentObj.size(); i++) {
		qEnvironmentObj[i]->draw(worldMat);
	}

	for (int i = 0; i < qPlayer.size(); i++) {
		Player* temp = (Player*)qPlayer[i];
		temp->draw(worldMat);
	}

	// gameState.top()->render();
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
