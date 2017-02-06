#pragma once

#include <math.h>
#include "src/game.h"
#include "src/CollisionManager.h"
#include "src/LevelManager.h"
#include "src/Menu.h"
#include "src/Instructions.h"

class quicky : public Game {

public:

	CollisionManager*			cManager;
	std::vector<VertexShape*>	qObstacles;
	std::vector<VertexShape*>	qPlayer;
	LevelManager*				lManager;
	rapidjson::Document			controlDoc;
	rapidjson::Document			obstacleDoc;
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
