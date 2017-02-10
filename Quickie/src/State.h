#pragma once

#include "input.h"
#include "Font.h"
#include "audio.h"

#include "rapidjson/document.h"

namespace fontsNS
{

	enum Fonts
	{
		DEFAULT,
		HEADING1,
		HEADING2,
		INSTRUCTIONS,
		SUBTITLE,
		GAME_SELECT,
		END_SCREEN
	};
}

namespace stateNS
{
	const int docID = 0;
	enum NextState
	{
		INSTRUCTIONS,
		GAMEPLAY,
		ENDSCREEN,
		REVERT
	};

	const UINT	sqr1X = GAME_WIDTH / 4;
	const UINT	sqr2X = (GAME_WIDTH / 4) * 3;
	const UINT	sqrY = (GAME_HEIGHT / 5) * 2;
}

class State
{

	void initFonts();
	void addFont(fontsNS::Fonts font, int height, UINT width, UINT weight, bool italics, std::string fontName);

protected:
	Graphics*				graphics;
	Input*					input;
	Audio*					audio;
	float*					deltaTime;

	D3DXMATRIX		worldMatrix;
	std::map<fontsNS::Fonts, Font>	fonts;
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

	virtual void initialize(Graphics* graphics, Input* input, Audio* audio, rapidjson::Document& doc, float* deltaTime);
	virtual void update() = 0;
	virtual void ai() = 0;
	virtual void render() = 0;
	virtual void collisions() = 0;
	virtual void releaseAll() = 0;
	virtual void resetAll() = 0;
};
