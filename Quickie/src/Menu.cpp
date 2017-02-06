#include "Menu.h"

Menu::Menu()
{
	menuStack.push(PLAY);
	firstGame = true;
};


Menu::~Menu(){};

void Menu::initialize(Graphics* g, Input* i, Audio* a , rapidjson::Document& doc)
{
	State::initialize(g, i, a, doc);
}


void Menu::update()
{
	switch (menuStack.top())
	{

	case PLAY:
		setCurrentSceneByInput(CONTROLS, controls.at(CONTROL_DOWN));
		if (input->getKeyState(controls.at(CONTROL_RIGHT)) && firstGame)
		{
			setNextStateByInput(stateNS::INSTRUCTIONS, controls.at(CONTROL_RIGHT));
			firstGame = false;
		}
		else if (input->getKeyState(controls.at(CONTROL_RIGHT)))
		{
			setNextStateByInput(stateNS::GAMEPLAY, controls.at(CONTROL_RIGHT));
		}
		break;

	case CONTROLS:
		setCurrentSceneByInput(REVERT, controls.at(CONTROL_UP));
		setCurrentSceneByInput(CONTROLS, controls.at(CONTROL_RIGHT));
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
	if (s == REVERT && s != PLAY)
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