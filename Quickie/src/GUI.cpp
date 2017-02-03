#include "GUI.h"

GUI::GUI()
{
	currentFont = NULL;
	stateStack = new std::stack<State>();
	fontMap = std::map<std::string, Font*>();
	graphics = nullptr;
	input = nullptr;
	game = nullptr;
	selectedItemIndex = 0;

	controls.insert(std::pair<guiNS::Control, int>(guiNS::CONTROL_UP, 0.1f));
	controls.insert(std::pair<guiNS::Control, int>(guiNS::CONTROL_DOWN, 0.1f));
	controls.insert(std::pair<guiNS::Control, int>(guiNS::CONTROL_LEFT, 0.1f));
	controls.insert(std::pair<guiNS::Control, int>(guiNS::CONTROL_RIGHT, 0.1f));
}

GUI::~GUI(){}

bool GUI::initialize(Game* g)
{
	try
	{
		game = g;
		graphics = game->getGraphics();
		input = game->getInput();
		stateStack->push(MENU_PLAY);
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
	this->addFont("MENU_OPTION", FONT_HEIGHT, FONT_WIDTH, FONT_WEIGHT, FONT_ITALICS, "yorkbailehill");
}

void GUI::initControls(rapidjson::Document& doc)
{
	controls.at(guiNS::CONTROL_UP) = doc["control"].GetArray()[0]["up"].GetInt();
	controls.at(guiNS::CONTROL_DOWN) = doc["control"].GetArray()[0]["down"].GetInt();
	controls.at(guiNS::CONTROL_LEFT) = doc["control"].GetArray()[0]["left"].GetInt();
	controls.at(guiNS::CONTROL_RIGHT) = doc["control"].GetArray()[0]["right"].GetInt();
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

void GUI::setCurrentState(State s)
{
	if (stateStack->top() != s)
		stateStack->push(s);
}

void GUI::setCurrentStateByInput(State s, int c)
{
	if (s == REVERT)
	{
		if (input->getKeyState(c))
		{
			if (!input->wasKeyPressed(c))
			{
				stateStack->pop();
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
				if (stateStack->top() != s)
					stateStack->push(s);
				input->keysPressed[c] = true;
			}
		}
		else
			input->clearKeyPress(c);
	}
}

void GUI::update()
{
	switch (stateStack->top())
	{

	case MENU_PLAY:
		setCurrentStateByInput(MENU_CONTROLS, controls.at(guiNS::CONTROL_DOWN));
		break;

	case MENU_CONTROLS:
		setCurrentStateByInput(REVERT, controls.at(guiNS::CONTROL_UP));
		setCurrentStateByInput(MENU_HIGHSCORE, controls.at(guiNS::CONTROL_DOWN));
		break;

	case MENU_HIGHSCORE:
		setCurrentStateByInput(REVERT, controls.at(guiNS::CONTROL_UP));
		break;

	/*case MENU_PLAY:
		if (input->getKeyState(DOWN_KEY))
		{
			if (!input->wasKeyPressed(DOWN_KEY))
			{
				setCurrentState(MENU_CONTROLS);
				input->keysPressed[DOWN_KEY] = true;
			}
		}

		break;

	case MENU_CONTROLS:
		if (input->getKeyState(UP_KEY))
		{
			if (!input->wasKeyPressed(UP_KEY))
			{
				revertState();
				input->keysPressed[UP_KEY] = true;
			}
		}
		else
			input->clearKeyPress(UP_KEY);

		if (input->getKeyState(DOWN_KEY))
		{
			if (!input->wasKeyPressed(DOWN_KEY))
			{
				setCurrentState(MENU_HIGHSCORE);
				input->keysPressed[DOWN_KEY] = true;
			}
		}
		else
			input->clearKeyPress(DOWN_KEY);

		break;

	case MENU_HIGHSCORE:
		if (input->getKeyState(UP_KEY))
		{
			if (!input->wasKeyPressed(UP_KEY))
			{
				revertState();
				input->keysPressed[UP_KEY] = true;
			}
		}
		break;
*/
	}
}

void GUI::render()
{
	switch (stateStack->top())
	{
	case MENU_PLAY:
	case MENU_CONTROLS:
	case MENU_HIGHSCORE:
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
		currentFont->print(
				GAME_WIDTH / 2 - currentFont->getTotalWidth("QUICKIE") / 2, 
				GAME_HEIGHT / 5, 
				"QUICKIE");
	}

	if (setFont("MENU_OPTION"))
	{
		int offSetY = 0;

		for (int i = 0; i < guiNS::optionsLength; ++i)
		{
			if (stateStack->top() == i)
			{
				currentFont->print(
					GAME_WIDTH / 2 - currentFont->getTotalWidth(("> " + guiNS::options[i])) / 2,
					GAME_HEIGHT / 3 + offSetY,
					"> " + guiNS::options[i]);
			}
			else
			{
				currentFont->print(
					GAME_WIDTH / 2 - currentFont->getTotalWidth(guiNS::options[i]) / 2,
					GAME_HEIGHT / 3 + offSetY,
					guiNS::options[i]);
			}
			

			offSetY += currentFont->getHeight();
		}
	}
}
