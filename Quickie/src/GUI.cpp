#include "GUI.h"

GUI::GUI()
{
	font = NULL;
	sceneStack = new std::stack<Scene>();
}

GUI::~GUI(){}

bool GUI::initialize(Font* f)
{
	try
	{
		font = f;
		sceneStack->push(MENU);
	}
	catch (...)
	{
		return false;
	}

	return true;
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
	font->print(GAME_WIDTH / 2, GAME_HEIGHT / 4, "QUICKIE");
}
