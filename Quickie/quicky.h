#pragma once

#include "src/game.h"
#include "src/CollisionManager.h"
#include "src/Font.h"
#include <math.h>
#include "src/GUI.h"

extern void game_init();
extern void game_preload();
extern void game_render_2d(float);
extern void game_render_sprite(float);
extern void game_update(float);

class quicky : public Game {

	Font*	font;
	GUI*			gui;

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

	void updateMouse();
	void updateKeyboard();
	void keyPress(int key);
	void keyRelease(int key);
	void mouseButton(int key);
	void mouseButtonRelease(int key);
	void mouseMove(int x, int y);
};
