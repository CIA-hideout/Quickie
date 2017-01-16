#pragma once

#include "src/game.h"
#include "src/entity.h"
#include "src/LTriangle.h"
#include "src/LSquare.h"
#include "src/Obstacle.h"

extern void game_init();
extern void game_preload();
extern void game_render_2d(float);
extern void game_render_sprite(float);
extern void game_update(float);

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

	void updateMouse();
	void updateKeyboard();
	void keyPress(int key);
	void keyRelease(int key);
	void mouseButton(int key);
	void mouseButtonRelease(int key);
	void mouseMove(int x, int y);
};
