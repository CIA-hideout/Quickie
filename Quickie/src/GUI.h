#ifndef _GUI_H_
#define _GUI_H_

#include "graphics.h"
#include "FontHandler.h"

class GUI
{
	FontHandler font;

public:
	GUI();
	~GUI();

	bool initialize(FontHandler font);
	void menu();
	void option(int i);

};
#endif