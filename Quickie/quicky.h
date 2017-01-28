#pragma once

#include "src/game.h"
#include "src/LTriangle.h"
#include "src/LSquare.h"
#include "src/Obstacle.h"
#include "src/Player.h"
#include "src/CollisionManager.h"
#include "src/FontHandler.h"
#include "src/graphics.h"

extern void game_init();
extern void game_preload();
extern void game_render_2d(float);
extern void game_render_sprite(float);
extern void game_update(float);

class quicky : public Game {

	FontHandler* font;

public:

	CollisionManager*			cManager;
	std::vector<VertexShape*>	vEntities;

	quicky();

	virtual ~quicky();

	void initialize(HWND hwnd);
	void update();
	void ai();
	void collisions();
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
