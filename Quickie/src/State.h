#ifndef _STATE_H
#define _STATE_H

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

class State
{

	void initFonts();
	void addFont(Fonts font, int height, UINT width, UINT weight, bool italics, std::string fontName);

protected:
	Graphics*				graphics;
	Input*					input;
	std::map<Fonts, Font>	fonts;
	std::map<Control, int>	controls;

public:
	State();
	virtual ~State();

	void initControls(rapidjson::Document&);

	virtual void initialize(Graphics* graphics, Input* input);
	virtual void update() = 0;
	virtual void ai() = 0;
	virtual void render() = 0;
	virtual void collisions() = 0;
	virtual void releaseAll() = 0;
	virtual void resetAll() = 0;
};

#endif