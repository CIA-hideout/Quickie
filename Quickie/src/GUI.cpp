#include "GUI.h"

GUI::GUI()
{
	currentFont = NULL;
	sceneStack = new std::stack<Scene>();
	fontMap = std::map<std::string, Font*>();
	graphics = nullptr;
}

GUI::~GUI(){}

bool GUI::initialize(Graphics* g)
{
	try
	{
		graphics = g;
		sceneStack->push(MENU);
		this->initFonts();
	}
	catch (...)
	{
		return false;
	}

	return true;
}

void GUI::initFonts()
{
	this->addFont("DEFAULT", FONT_HEIGHT, FONT_WIDTH, FONT_WEIGHT, FONT_ITALICS, FONT_NAME);
	this->addFont("MENU_TITLE", FONT_HEIGHT * 1.5, FONT_WIDTH * 1.5, FONT_WEIGHT, FONT_ITALICS, FONT_NAME);
}

void GUI::addFont(std::string s, int h, UINT wid, UINT wei, bool i, std::string fN)
{
	currentFont = new Font();

	if (!currentFont->initialize(graphics))
		throw(GameError(gameErrorNS::FATAL_ERROR, "FAIL TO INITIALIZE FONT"));

	if (!currentFont->createFont(h, wid, wei, i, fN))
		throw(GameError(gameErrorNS::FATAL_ERROR, "FAIL TO CREATE " + s + " FONT"));
	
	fontMap[s] = currentFont;
}


bool GUI::setFont(std::string s)
{
	if (fontMap.find(s) != fontMap.end())	// if font found
	{
		currentFont = fontMap[s];			// set font
		return true;
	}

	return false;
}


void GUI::render()
{
	switch (sceneStack->top())
	{
	case MENU:
		this->renderMenu();
		break;

	case GAME:
		
		break;
	}
}

void GUI::renderMenu()
{
	if (setFont("MENU_TITLE"))
	{
		currentFont->print(GAME_WIDTH / 2, GAME_HEIGHT / 4, "QUICKIE");
	}
}
