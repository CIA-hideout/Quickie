#pragma once

#include "input.h"
#include "Font.h"
#include "rapidjson/document.h"

enum Fonts
{
	DEFAULT,
	MENU_TITLE,
	MENU_OPTIONS,
	GAME
};

namespace stateNS
{
	enum NextState
	{
		INSTRUCTIONS,
		GAMEPLAY,
		HIGHSCORE,
		REVERT
	};
}

class State
{

	void initFonts();
	void addFont(Fonts font, int height, UINT width, UINT weight, bool italics, std::string fontName);

protected:
	Graphics*				graphics;
	Input*					input;
	std::map<Fonts, Font>	fonts;
	std::map<Control, int>	controls;
	stateNS::NextState		nextState;
	stateNS::NextState*		pNextState = nullptr;

public:
	State();
	virtual ~State();

	void					initControls(rapidjson::Document&);
	stateNS::NextState*		getNextState(){ return pNextState; }
	void					clearNextState(){ pNextState = nullptr; }

	virtual void initialize(Graphics* graphics, Input* input);
	virtual void update() = 0;
	virtual void ai() = 0;
	virtual void render() = 0;
	virtual void collisions() = 0;
	virtual void releaseAll() = 0;
	virtual void resetAll() = 0;
};
