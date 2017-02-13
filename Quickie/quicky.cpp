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

	// Initalize menu
	menu = new Menu();
	menu->initialize(graphics, input, audio, controlDoc, &deltaTime);

	// Start game state in menu
	gameState.push(menu);
}

void quicky::update() {

	gameState.top()->update();

	if (gameState.top()->getNextState() != nullptr)
	{
		stateNS::NextState pState = *gameState.top()->getNextState();
		gameState.top()->clearNextState();

		switch (pState)
		{
		case stateNS::INSTRUCTIONS:
		{
			Instructions* i = new Instructions();

			i->initialize(graphics, input, audio, controlDoc, &deltaTime);
			gameState.push(i);
		}
			break;

		case stateNS::GAMEPLAY:
		{
			Gameplay* g = new Gameplay();
			g->menu = menu;
			g->initialize(graphics, input, audio, controlDoc, &deltaTime);
			gameState.push(g);
		}
			break;

		case stateNS::ENDSCREEN:
		{
			EndScreen* e = new EndScreen();
			e->menu = menu;
			e->initialize(graphics, input, audio, controlDoc, &deltaTime);
			gameState.push(e);
		}
			break;

		case stateNS::REVERT:
		{
			audio->stopCue(BGMRand);
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
