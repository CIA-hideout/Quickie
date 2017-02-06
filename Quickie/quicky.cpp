#include "quicky.h"

<<<<<<< HEAD
=======

Obstacle* o1 = new Obstacle(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1), COLOR_PURPLE);
Obstacle* o2 = new Obstacle(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1), COLOR_PURPLE);
Obstacle* o3 = new Obstacle(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1), COLOR_PURPLE);
Obstacle* o4 = new Obstacle(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1), COLOR_PURPLE);
Obstacle* o5 = new Obstacle(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1), COLOR_PURPLE);
Obstacle* o6 = new Obstacle(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(1, 1, 1), COLOR_PURPLE);

Wall* w1 = new Wall(D3DXVECTOR3(0, 22, 19.5), DIMENSION_HORIZONTAL_WALL, D3DXVECTOR3(1, 1, 1), COLOR_GRAY);		// - up
Wall* w2 = new Wall(D3DXVECTOR3(0, -22, 19.5), DIMENSION_HORIZONTAL_WALL, D3DXVECTOR3(1, 1, 1), COLOR_GRAY);	// - down
Wall* w3 = new Wall(D3DXVECTOR3(-21, 0, 19.5), DIMENSION_VERTICAL_WALL, D3DXVECTOR3(1, 1, 1), COLOR_GRAY);		// | left
Wall* w4 = new Wall(D3DXVECTOR3(21, 0, 19.5), DIMENSION_VERTICAL_WALL, D3DXVECTOR3(1, 1, 1), COLOR_GRAY);		// | right

Player* sqr1 = new Player(D3DXVECTOR3(0, 0, 20 - 1), D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 255, 255));
Player* sqr2 = new Player(D3DXVECTOR3(10, 10, 20 - 1), D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 240, 240));

>>>>>>> Add randomiseDimension function for Obstacles
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

	// parse player control
	FILE* controlFile = fopen("resource\\data\\control.json", "rb");
	char controlBuffer[1024];
	rapidjson::FileReadStream is(controlFile, controlBuffer, sizeof(controlBuffer));
	controlDoc.ParseStream(is);
	printf("%s\n", controlDoc["test_string"].GetString());
	fclose(controlFile);

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
