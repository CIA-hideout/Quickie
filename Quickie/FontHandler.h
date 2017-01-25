#pragma once
#ifndef _FONTHANDLER_H_
#define _FONTHANDLER_H_

#include <map>
#include <string>

#include "src/image.h"
#include "src/"

class Font{
public:
	Font();

	void initialize()
	bool loadTextData(std::string fileName);		// text data (widths) is stored in dat files
	void Print(int x, int y, std::string text);		// prints the text on screen give the coordinates
	void Print_(int x, int y, std::string text);		// prints the text on screen give the coordinates
	virtual void draw();
	void update(float deltaTime);

	int getTotalWidth(std::string text);
	int getTotalWidth_(std::string text);

private:

	int				widths[256];
	Graphics 

};

#endif