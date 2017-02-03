#pragma once

#include <math.h>
#include "src/game.h"
#include "src/CollisionManager.h"
#include "src/Font.h"
#include "src/Menu.h"

class quicky : public Game {

public:

	CollisionManager*			cManager;
	std::vector<VertexShape*>	qObstacles;
	std::vector<VertexShape*>	qPlayer;
	rapidjson::Document			controlDoc;

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
	void popState() { gameState.pop(); }
	void pushState(State* s){ gameState.push(s); }
};
