#pragma once

#include "src/game.h"
#include "src/CollisionManager.h"
#include "src/FontHandler.h"
#include <math.h>

class quicky : public Game {

	FontHandler* font;

public:

	CollisionManager*			cManager;
	std::vector<VertexShape*>	vEntities;
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
};
