#pragma once
#ifndef _FONTHANDLER_H_
#define _FONTHANDLER_H_

#include <map>
#include "image.h"

class FontHandler : public Image {
	int						widths[256];
	Graphics*				g;
	//FontHandlerNS::Fonts	currentFont;

public:
	FontHandler();
	~FontHandler();

	bool initialize(Graphics* g, int width, int height, int ncols, TextureManager* tM);
	void draw();
	void print(int x, int y, std::string text);		// prints the text on screen give the coordinates

	int getTotalWidth(std::string text);
	//void setCurrentFont(FontHandlerNS::Fonts font);
};

#endif