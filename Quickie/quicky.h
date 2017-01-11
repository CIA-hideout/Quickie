#pragma once

#include "src/game.h"
#include "src/entity.h"
#include "src/LTriangle.h"


class quicky : public Game {

public:

	quicky();

	virtual ~quicky();

	void initialize(HWND hwnd);
	void update();
	void ai();
	void collisions();
	void collisions(Entity* entity);
	void render();
	void releaseAll();
	void resetAll();
};
