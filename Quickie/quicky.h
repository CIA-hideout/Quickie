#pragma once

#include <math.h>
#include "src/game.h"
#include "src/Menu.h"
#include "src/Instructions.h"
#include "src/Gameplay.h"
#include "src/EndScreen.h"

class quicky : public Game {

public:

	rapidjson::Document			controlDoc;
	std::stack<State*>			gameState;

	quicky();

	virtual ~quicky();

	void initialize(HWND hwnd);
	void update();
	void ai();
	void collisions();
	void render();
	void releaseAll();
	void resetAll();

	void updateKeyboard();
	void keyPress(int key);
	void keyRelease(int key);
};
