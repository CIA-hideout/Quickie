#pragma once
#ifndef _FONTHANDLER_H_
#define _FONTHANDLER_H_

#include "graphics.h"

class FontHandler{
	Graphics*	graphics;
	ID3DXFont*	font;
	RECT*		font_rect;

	// current font's values
	int height;
	UINT width, weight;
	bool italics;
	std::string fontName;

public:
	FontHandler();
	~FontHandler();

	bool initialize(Graphics* graphics);
	bool createFont();
	bool createFont(int height, UINT width, UINT weight, bool i, std::string fN);
	void print(int x, int y, std::string sentence);						// prints the text on screen given the coordinates

	RECT* getFontRect(){ return font_rect; }
	int getTotalWidth(std::string text);
	//void setCurrentFont(FontHandlerNS::Fonts font);

	//void setHeight(int height) { height = height; }
	//void setWidth(int width) { width = width; }
};

#endif