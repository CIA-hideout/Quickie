#ifndef _GUI_H_
#define _GUI_H_

#include "Font.h"
#include <stack>

enum Scene
{
	MENU,					// main menu;		when is it displayed
	GAME,					// hud;				during gameplay
	INSTRUCTIONS,			// instructions;	during 1st gameplay only
	CONTROLS,				// instructions;	in the menu
	HIGHSCORE				// leaderboard;		in the menu
};

class GUI
{
	std::stack<Scene>*		sceneStack;
	Font*			font;

	void renderMenu();
public:
	GUI();
	~GUI();

	bool initialize(Font* f);
	void render();
	void setCurrentScene(Scene s){ sceneStack->push(s); };
	void revertScene(){ sceneStack->pop(); };

	// GET
	Font* getFont(){ return font; }

	// SET
	void setFont(Font* f){ font = f; }

};
#endif