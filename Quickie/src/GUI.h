#ifndef _GUI_H_
#define _GUI_H_

#include <stack>
#include <map>
#include "Font.h"
#include "graphics.h"
#include "game.h"

enum State
{
	MENU_PLAY,				// main menu;		when is it displayed
	MENU_CONTROLS,			//
	MENU_HIGHSCORE,			//
	GAME,					// hud;				during gameplay
	INSTRUCTIONS,			// instructions;	during 1st gameplay only
	CONTROLS,				// instructions;	in the menu
	HIGHSCORE				// leaderboard;		in the menu
};

namespace guiNS
{
	const std::string				options[] = {"Play!", "Controls", "Highscore"};
	const int						optionsLength = 3;
}

class GUI
{
	std::stack<State>*				stateStack;
	std::map<std::string, Font*>	fontMap;
	Font*							currentFont;
	Graphics*						graphics;
	Game*							game;
	Input*							input;
	int								selectedItemIndex;

	void initFonts();
	//void initControls(rapidjson::Document&);
	void renderMenu();
	void addFont(std::string text, int height, UINT width, UINT weight, bool italics, std::string fontName);

public:
	GUI();
	~GUI();
	bool initialize(Game* game);
	void update();
	void render();
	void setCurrentState(State s);
	void revertState(){ stateStack->pop(); };


	// GET
	Font* getFont(){ return currentFont; }

	// SET
	bool setFont(std::string text);

};
#endif