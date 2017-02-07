#pragma once

#include "input.h"
#include "Font.h"
#include "audio.h"

#include "rapidjson/document.h"

enum Fonts
{
	DEFAULT,
	MENU_TITLE,
	MENU_OPTIONS,
	GAME,
	GAME_SELECT
};

namespace stateNS
{
	const int docID = 0;
	enum NextState
	{
		INSTRUCTIONS,
		GAMEPLAY,
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
	Audio*					audio;
	std::map<Fonts, Font>	fonts;
	std::map<Control, int>	controls;
	stateNS::NextState		nextState;
	stateNS::NextState*		pNextState = nullptr;

public:
	State();
	virtual ~State();

	void					assignControls(rapidjson::Document&);
	stateNS::NextState*		getNextState(){ return pNextState; }
	void					setNextStateByInput(stateNS::NextState nS, int key);
	void					clearNextState(){ pNextState = nullptr; }

	virtual void initialize(Graphics* graphics, Input* input, Audio* audio, rapidjson::Document& doc);
	virtual void update() = 0;
	virtual void ai() = 0;
	virtual void render() = 0;
	virtual void collisions() = 0;
	virtual void releaseAll() = 0;
	virtual void resetAll() = 0;
};
