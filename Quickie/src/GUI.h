#ifndef _GUI_H_
#define _GUI_H_

#include <stack>
#include <map>
#include "Font.h"
#include "graphics.h"

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
	std::stack<Scene>*				sceneStack;
	std::map<std::string, Font*>	fontMap;
	Font*							currentFont;
	Graphics*						graphics;

	void initFonts();
	void renderMenu();
	void addFont(std::string, int h, UINT wid, UINT wei, bool i, std::string fN);
public:
	GUI();
	~GUI();

	bool initialize(Graphics* g);
	void render();
	void setCurrentScene(Scene s){ sceneStack->push(s); };
	void revertScene(){ sceneStack->pop(); };

	// GET
	Font* getFont(){ return currentFont; }

	// SET
	bool setFont(std::string s);

};
#endif