#pragma once

#include "src/game.h"
#include "src/CollisionManager.h"
#include "src/Font.h"
#include "src/LevelManager.h"
#include <math.h>
#include "src/GUI.h"

class quicky : public Game {

	GUI*			gui;

public:

	CollisionManager*			cManager;
	std::vector<VertexShape*>	qObstacles;
	std::vector<VertexShape*>	qPlayer;
	LevelManager*				lManager;
	rapidjson::Document			controlDoc;
	rapidjson::Document			obstacleDoc;

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
