#ifndef _GUI_H_
#define _GUI_H_

#include "FontHandler.h"
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
	FontHandler*			font;

	void renderMenu();
public:
	GUI();
	~GUI();

	bool initialize(FontHandler* f);
	void render();
	void setCurrentScene(Scene s){ sceneStack->push(s); };
	void revertScene(){ sceneStack->pop(); };

};
#endif