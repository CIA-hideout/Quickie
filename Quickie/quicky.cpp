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

	// parse player control
	FILE* controlFile = fopen("resource\\data\\control.json", "rb");
	char controlBuffer[1024];
	rapidjson::FileReadStream is(controlFile, controlBuffer, sizeof(controlBuffer));
	controlDoc.ParseStream(is);
	printf("%s\n", controlDoc["test_string"].GetString());
	fclose(controlFile);

	// Initialize menu
	Menu* menu = new Menu();
	menu->initialize(graphics, input, audio, controlDoc);

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
