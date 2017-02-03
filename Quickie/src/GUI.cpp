//#include "GUI.h"
//
//GUI::GUI()
//{
//	currentFont = NULL;
//	stateStack = new std::stack<State>();
//	fontMap = std::map<std::string, Font*>();
//	graphics = nullptr;
//	game = nullptr;
//
//	controls.insert(std::pair<guiNS::Control, int>(guiNS::CONTROL_UP, 0.1f));
//	controls.insert(std::pair<guiNS::Control, int>(guiNS::CONTROL_DOWN, 0.1f));
//	controls.insert(std::pair<guiNS::Control, int>(guiNS::CONTROL_LEFT, 0.1f));
//	controls.insert(std::pair<guiNS::Control, int>(guiNS::CONTROL_RIGHT, 0.1f));
//}
//
//GUI::~GUI(){}
//
//bool GUI::initialize(Game* g)
//{
//	try
//	{
//		game = g;
//		graphics = game->getGraphics();
//		input = game->getInput();
//		stateStack->push(MENU_PLAY);
//		this->initFonts();
//	}
//	catch (...)
//	{
//		return false;
//	}
//
//	return true;
//}
//
//void GUI::initFonts()
//{
//	this->addFont("DEFAULT", guiNS::FONT_HEIGHT, guiNS::FONT_WIDTH, guiNS::FONT_WEIGHT, guiNS::FONT_ITALICS, guiNS::FONT_NAME);
//	this->addFont("MENU_TITLE", guiNS::FONT_HEIGHT * 1.5, guiNS::FONT_WIDTH * 1.5, guiNS::FONT_WEIGHT, guiNS::FONT_ITALICS, guiNS::FONT_NAME);
//	this->addFont("MENU_OPTION", guiNS::FONT_HEIGHT, guiNS::FONT_WIDTH, guiNS::FONT_WEIGHT, guiNS::FONT_ITALICS, "yorkbailehill");
//	this->addFont("GAME", guiNS::FONT_HEIGHT / 2, guiNS::FONT_WIDTH / 20, guiNS::FONT_WEIGHT / 5, guiNS::FONT_ITALICS, "HeartFont");
//}
//
//void GUI::initControls(rapidjson::Document& doc)
//{
//	controls.at(guiNS::CONTROL_UP) = doc["control"].GetArray()[0]["up"].GetInt();
//	controls.at(guiNS::CONTROL_DOWN) = doc["control"].GetArray()[0]["down"].GetInt();
//	controls.at(guiNS::CONTROL_LEFT) = doc["control"].GetArray()[0]["left"].GetInt();
//	controls.at(guiNS::CONTROL_RIGHT) = doc["control"].GetArray()[0]["right"].GetInt();
//}
//
//void GUI::update()
//{
//	switch (stateStack->top())
//	{
//
//	case MENU_PLAY:
//		setCurrentStateByInput(MENU_CONTROLS, controls.at(guiNS::CONTROL_DOWN));
//		setCurrentStateByInput(GAME, controls.at(guiNS::CONTROL_RIGHT));
//		break;
//
//	case MENU_CONTROLS:
//		setCurrentStateByInput(REVERT, controls.at(guiNS::CONTROL_UP));
//		setCurrentStateByInput(MENU_HIGHSCORE, controls.at(guiNS::CONTROL_DOWN));
//		setCurrentStateByInput(CONTROLS, controls.at(guiNS::CONTROL_RIGHT));
//		break;
//
//	case MENU_HIGHSCORE:
//		setCurrentStateByInput(REVERT, controls.at(guiNS::CONTROL_UP));
//		setCurrentStateByInput(HIGHSCORE, controls.at(guiNS::CONTROL_RIGHT));
//		break;
//
//	case GAME:
//		setCurrentStateByInput(REVERT, controls.at(guiNS::CONTROL_LEFT));
//
//	case CONTROLS:
//		setCurrentStateByInput(REVERT, controls.at(guiNS::CONTROL_LEFT));
//		break;
//
//	case HIGHSCORE:
//		setCurrentStateByInput(REVERT, controls.at(guiNS::CONTROL_LEFT));
//		break;
//
//	}
//}
//
//void GUI::render()
//{
//	switch (stateStack->top())
//	{
//	case MENU_PLAY:
//	case MENU_CONTROLS:
//	case MENU_HIGHSCORE:
//		renderMenu();
//		break;
//
//	case GAME:
//		renderGame();
//		break;
//
//	case CONTROLS:
//		renderControls();
//		break;
//
//	case HIGHSCORE:
//		renderHighscore();
//		break;
//
//	}
//}
//
//void GUI::renderMenu()
//{
//	if (setFont("MENU_TITLE"))
//	{
//		currentFont->print(
//				GAME_WIDTH / 2 - currentFont->getTotalWidth("QUICKIE") / 2, 
//				GAME_HEIGHT / 5, 
//				"QUICKIE");
//	}
//
//	if (setFont("MENU_OPTION"))
//	{
//		int offSetY = 0;
//
//		for (int i = 0; i < guiNS::optionsLength; ++i)
//		{
//			if (stateStack->top() == i)
//			{
//				currentFont->print(
//					GAME_WIDTH / 2 - currentFont->getTotalWidth(("> " + guiNS::options[i])) / 2,
//					GAME_HEIGHT / 3 + offSetY,
//					"> " + guiNS::options[i]);
//			}
//			else
//			{
//				currentFont->print(
//					GAME_WIDTH / 2 - currentFont->getTotalWidth(guiNS::options[i]) / 2,
//					GAME_HEIGHT / 3 + offSetY,
//					guiNS::options[i]);
//			}
//			
//
//			offSetY += currentFont->getHeight();
//		}
//	}
//}
//
//void GUI::renderGame()
//{
//	Font* tempFont;
//
//	if (setFont("MENU_TITLE"))
//	{
//		tempFont = currentFont;
//		currentFont->print(
//			GAME_WIDTH / 2 - currentFont->getTotalWidth("YOU ARE IN GAME!") / 2,
//			GAME_HEIGHT / 5,
//			"YOU ARE IN GAME!");
//
//		currentFont->print(
//			0,
//			GAME_HEIGHT - currentFont->getHeight(),
//			"P1");
//
//		currentFont->print(
//			GAME_WIDTH - currentFont->getTotalWidth("P2"),
//			GAME_HEIGHT - currentFont->getHeight(),
//			"P2");
//	}
//
//	if (setFont("GAME"))
//	{
//		currentFont->print(
//			tempFont->getTotalWidth("P1"),
//			GAME_HEIGHT - currentFont->getHeight() * 2.5,
//			"BBB");
//	}
//}
//
//void GUI::renderControls()
//{
//	if (setFont("MENU_OPTION"))
//	{
//		currentFont->print(
//			GAME_WIDTH / 2 - currentFont->getTotalWidth("SORRY, I CAN'T HELP YOU RIGHT NOW") / 2,
//			GAME_HEIGHT / 5,
//			"SORRY, I CAN'T HELP YOU RIGHT NOW");
//	}
//}
//
//void GUI::renderHighscore()
//{
//	if (setFont("MENU_OPTION"))
//	{
//		currentFont->print(
//			GAME_WIDTH / 2 - currentFont->getTotalWidth("YOU ARE NOT THE TOP SCORER!") / 2,
//			GAME_HEIGHT / 5,
//			"YOU ARE NOT THE TOP SCORER!");
//	}
//}
//
//void GUI::addFont(std::string s, int h, UINT wid, UINT wei, bool i, std::string fN)
//{
//	currentFont = new Font();
//
//	if (!currentFont->initialize(graphics))
//		throw(GameError(gameErrorNS::FATAL_ERROR, "FAIL TO INITIALIZE FONT"));
//
//	if (!currentFont->createFont(h, wid, wei, i, fN))
//		throw(GameError(gameErrorNS::FATAL_ERROR, "FAIL TO CREATE " + s + " FONT"));
//
//	fontMap[s] = currentFont;
//}
//
//
//bool GUI::setFont(std::string s)
//{
//	if (fontMap.find(s) != fontMap.end())	// if font found
//	{
//		currentFont = fontMap[s];			// set font
//		return true;
//	}
//
//	return false;
//}
//
