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

	w1 = new Wall(D3DXVECTOR3(0,  29, 19.5), DIMENSION_HORIZONTAL_WALL, D3DXVECTOR3(1, 1, 1), COLOR_RED);		// - up
	w2 = new Wall(D3DXVECTOR3(0, -29, 19.5), DIMENSION_HORIZONTAL_WALL, D3DXVECTOR3(1, 1, 1), COLOR_RED);	// - down
	w3 = new Wall(D3DXVECTOR3(-25, 0, 19.5), DIMENSION_VERTICAL_WALL, D3DXVECTOR3(1, 1, 1), COLOR_RED);		// | left
	w4 = new Wall(D3DXVECTOR3( 25, 0, 19.5), DIMENSION_VERTICAL_WALL, D3DXVECTOR3(1, 1, 1), COLOR_RED);		// | right

	sqr1 = new Player(D3DXVECTOR3(0, 0, 20 - 1), D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(240, 240, 0));
	sqr2 = new Player(D3DXVECTOR3(10, 10, 20 - 1), D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 240, 240));

	gameStack.push(gameplayNS::LEVEL_1);
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
}

void Gameplay::update()
{
	if (!gameplay)
	{
		switch (gameStack.top())
		{
			case gameplayNS::LEVEL_1:
				setCurrentSceneByInput(gameplayNS::LEVEL_2, controls.at(CONTROL_DOWN));
				setCurrentSceneByInput(gameplayNS::LEVEL_1, controls.at(CONTROL_RIGHT));
				break;

			case gameplayNS::LEVEL_2:
				setCurrentSceneByInput(gameplayNS::REVERT, controls.at(CONTROL_UP));
				setCurrentSceneByInput(gameplayNS::LEVEL_3, controls.at(CONTROL_DOWN));
				setCurrentSceneByInput(gameplayNS::LEVEL_2, controls.at(CONTROL_RIGHT));
				break;

			case gameplayNS::LEVEL_3:
				setCurrentSceneByInput(gameplayNS::REVERT, controls.at(CONTROL_UP));
				setCurrentSceneByInput(gameplayNS::LEVEL_SHUFFLE, controls.at(CONTROL_DOWN));
				setCurrentSceneByInput(gameplayNS::LEVEL_3, controls.at(CONTROL_RIGHT));
				break;

			case gameplayNS::LEVEL_SHUFFLE:
				setCurrentSceneByInput(gameplayNS::REVERT, controls.at(CONTROL_UP));
				setCurrentSceneByInput(gameplayNS::LEVEL_RANDOM, controls.at(CONTROL_DOWN));
				setCurrentSceneByInput(gameplayNS::LEVEL_SHUFFLE, controls.at(CONTROL_RIGHT));
				break;

			case gameplayNS::LEVEL_RANDOM:
				setCurrentSceneByInput(gameplayNS::REVERT, controls.at(CONTROL_UP));
				setCurrentSceneByInput(gameplayNS::LEVEL_RANDOM, controls.at(CONTROL_RIGHT));

				break;
		}
	}

	else
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
}

void Gameplay::render()
{
	if (!gameplay)
	{
		Font f;

		// Set Fonts for Level Select Title
		f = fonts.at(fontsNS::HEADING1);

		f.print(
			GAME_WIDTH / 2 - f.getTotalWidth("LEVEL SELECT") / 2,
			GAME_HEIGHT / 5,
			"LEVEL SELECT");

		f = fonts.at(fontsNS::HEADING2);

		// Set Fonts for Options'
		f = fonts.at(fontsNS::GAME_SELECT);
		int offSetY = 0;

		for (int i = 0; i < gameplayNS::optionsLength; ++i) {
			if (gameStack.top() == i) {
				f.print(
					GAME_WIDTH / 2 - f.getTotalWidth(("> " + gameplayNS::options[i])) / 2,
					GAME_HEIGHT / 2 + offSetY,
					"> " + gameplayNS::options[i]);
			}
			else {
				f.print(
					GAME_WIDTH / 2 - f.getTotalWidth(gameplayNS::options[i]) / 2,
					GAME_HEIGHT / 2 + offSetY,
					gameplayNS::options[i]);
			}


			offSetY += f.getHeight();
		}

	}

	else {
		for (int i = 0; i < qEnvironmentObj.size(); i++) {
			qEnvironmentObj[i]->draw(worldMatrix);
		}

		for (int i = 0; i < qPlayer.size(); i++) {
			Player* temp = (Player*)qPlayer[i];
			temp->draw(worldMatrix);
		}
		setNextStateByInput(stateNS::REVERT, controls.at(CONTROL_ESC));
	}
}


void Gameplay::setCurrentSceneByInput(gameplayNS::Mode m, int c) {
	// IF Player goes up
	if (m == gameplayNS::REVERT && m != gameplayNS::LEVEL_1) {
		if (input->getKeyState(c)) {
			if (!input->wasKeyPressed(c)) {
				gameStack.pop();
				input->keysPressed[c] = true;
			}
		}
		else
			input->clearKeyPress(c);
	}
	// IF Player SELECTS
	else if (c == controls.at(CONTROL_RIGHT)) {
		if (input->getKeyState(c)) {
			if (!input->wasKeyPressed(c)) {
				selectedMode = m;
				gameplay = true;
				input->keysPressed[c] = true;

				// levels are init here because if there are init in the init(),
				// selectedMode is empty
				// user selects after init is run
				switch (selectedMode) {
				case gameplayNS::LEVEL_1:
					lManager->setLevelOne(qEnvironmentObj);
					break;

				case gameplayNS::LEVEL_2:
					lManager->setLevelTwo(qEnvironmentObj);
					break;

				case gameplayNS::LEVEL_3:
					lManager->setLevelThree(qEnvironmentObj);
					break;

				case gameplayNS::LEVEL_SHUFFLE:
					lManager->setShuffle(qEnvironmentObj);
					break;

				case gameplayNS::LEVEL_RANDOM:
					lManager->setRandom(qEnvironmentObj, qPlayer);

					break;
				}
			}
		}
		else
			input->clearKeyPress(c);
	}
	else {
		if (input->getKeyState(c)) {
			if (!input->wasKeyPressed(c)) {
				if (gameStack.top() != m)
					gameStack.push(m);
				input->keysPressed[c] = true;
			}
		}
		else
			input->clearKeyPress(c);
	}
}

void Gameplay::selectMode(gameplayNS::Mode, int)
{

}
