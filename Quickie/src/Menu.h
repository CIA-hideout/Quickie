#ifndef _MENU_H_
#define _MENU_H_

#include <stack>
#include "State.h"

enum Scene
{
		PLAY,				// main menu;		when is it displayed
		CONTROLS,			//
		HIGHSCORE,			//
		REVERT
};

namespace menuNS
{
	const std::string				options[] = { "Play!", "Controls", "Highscore" };
	const int						optionsLength = 3;

}

class Menu : public State
{
	std::stack<Scene>		menuStack;

	void setCurrentSceneByInput(Scene s, int);
public:
	Menu();
	virtual ~Menu();
	
	void initialize(Graphics* graphics, Input* i);
	void update();
	void ai(){};
	void render();
	void collisions(){};
	void releaseAll(){};
	void resetAll(){};
};
#endif