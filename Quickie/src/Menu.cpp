#include "Menu.h"

Menu::Menu()
{
	menuStack.push(PLAY);
};


Menu::~Menu(){};

void Menu::initialize(Graphics* g, Input* i)
{
	State::initialize(g, i);
}


void Menu::update()
{
	switch (menuStack.top())
	{

	case PLAY:
		setCurrentSceneByInput(CONTROLS, controls.at(CONTROL_DOWN));
		break;

	case CONTROLS:
		setCurrentSceneByInput(REVERT, controls.at(CONTROL_UP));
		setCurrentSceneByInput(HIGHSCORE, controls.at(CONTROL_DOWN));
		setCurrentSceneByInput(CONTROLS, controls.at(CONTROL_RIGHT));
		break;

	case HIGHSCORE:
		setCurrentSceneByInput(REVERT, controls.at(CONTROL_UP));
		setCurrentSceneByInput(HIGHSCORE, controls.at(CONTROL_RIGHT));
		break;
	}
}

void Menu::render()
{
	Font f;

	f = fonts.at(MENU_TITLE);

	f.print(
		GAME_WIDTH / 2 - f.getTotalWidth("QUICKIE") / 2,
		GAME_HEIGHT / 5,
		"QUICKIE");

	f = fonts.at(MENU_OPTIONS);
	int offSetY = 0;

	for (int i = 0; i < menuNS::optionsLength; ++i)
	{
		if (menuStack.top() == i)
		{
			f.print(
				GAME_WIDTH / 2 - f.getTotalWidth(("> " + menuNS::options[i])) / 2,
				GAME_HEIGHT / 3 + offSetY,
				"> " + menuNS::options[i]);
		}
		else
		{
			f.print(
				GAME_WIDTH / 2 - f.getTotalWidth(menuNS::options[i]) / 2,
				GAME_HEIGHT / 3 + offSetY,
				menuNS::options[i]);
		}


		offSetY += f.getHeight();
	}
}

void Menu::setCurrentSceneByInput(Scene s, int c)
{
	if (s == REVERT)
	{
		if (input->getKeyState(c))
		{
			if (!input->wasKeyPressed(c))
			{
				menuStack.pop();
				input->keysPressed[c] = true;
			}
		}
		else
			input->clearKeyPress(c);
	}
	else
	{
		if (input->getKeyState(c))
		{
			if (!input->wasKeyPressed(c))
			{
				if (menuStack.top() != s)
					menuStack.push(s);
				input->keysPressed[c] = true;
			}
		}
		else
			input->clearKeyPress(c);
	}
}