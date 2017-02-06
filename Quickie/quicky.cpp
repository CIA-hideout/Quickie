#include "quicky.h"

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

<<<<<<< HEAD
=======
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

	// Initialize menu
	Menu* menu = new Menu();
	menu->initialize(this->getGraphics(), this->getInput());

	// Start game state in menu
	gameState.push(menu);

>>>>>>> Add Walls
	// parse player control
	FILE* controlFile = fopen("resource\\data\\control.json", "rb");
	char controlBuffer[1024];
	rapidjson::FileReadStream is(controlFile, controlBuffer, sizeof(controlBuffer));
	controlDoc.ParseStream(is);
	printf("%s\n", controlDoc["test_string"].GetString());
	fclose(controlFile);

<<<<<<< HEAD
	// Initialize menu
	Menu* menu = new Menu();
	menu->initialize(graphics, input, audio, controlDoc);
=======
	for (int i = 0; i < qEnvironmentObj.size(); i++) {
		Obstacle* temp = (Obstacle*)qEnvironmentObj[i];
	  temp->init(this->audio, this->graphics);
	}

	// init players
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
		if (tempObs->objectType == OBJECT_TYPE_OBSTACLE)
			tempObs->assign(obstacleDoc);
	}

	lManager->setRandomLevel(qEnvironmentObj);

	sqr1->assignControl(controlDoc);
	sqr2->assignControl(controlDoc);
	menu->initControls(controlDoc);
>>>>>>> Add Walls

	// Start game state in menu
	gameState.push(menu);
}

void quicky::update() {

	gameState.top()->update();

	if (gameState.top()->getNextState() != nullptr)
	{
		printf("NEXT STATE\n");
		stateNS::NextState pState = *gameState.top()->getNextState();
		gameState.top()->clearNextState();

		switch (pState)
		{
		case stateNS::INSTRUCTIONS:
		{
			printf("INSTRUCTIONS\n");
			Instructions* i = new Instructions();

			i->initialize(graphics, input, audio, controlDoc);
			gameState.push(i);
		}
			break;

		case stateNS::GAMEPLAY:
		{
			printf("GAMEPLAY\n");
			Gameplay* g = new Gameplay();

			g->initialize(graphics, input, audio, controlDoc, &deltaTime);
			gameState.push(g);
		}
			break;

		case stateNS::REVERT:
		{
			printf("REVERT\n");
			gameState.pop();
		}
			break;
		}
	}
<<<<<<< HEAD
=======

	for (int i = 0; i < qPlayer.size(); i++) {
		Player* temp = (Player*)qPlayer[i];
		temp->update(deltaTime, qEnvironmentObj);

	}
	graphics->camera->update(deltaTime);
>>>>>>> Add Walls
}

void quicky::ai() {

}

void quicky::collisions() {

}

void quicky::render()
{
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
