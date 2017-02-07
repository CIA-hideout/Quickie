#include "State.h"

State::State()
{
	input = nullptr;
	fonts = std::map<fontsNS::Fonts, Font>();
	graphics = nullptr;
	pNextState = nullptr;
};


State::~State(){};

void State::initialize(Graphics* g, Input* i, Audio* a, rapidjson::Document& doc)
{
	graphics = g;
	input = i;
	audio = a;
	initFonts();
	assignControls(doc);
}

void State::initFonts()
{
	addFont(fontsNS::DEFAULT, fontNS::FONT_HEIGHT, fontNS::FONT_WIDTH, fontNS::FONT_WEIGHT, fontNS::FONT_ITALICS, fontNS::FONT_NAME);
	addFont(fontsNS::HEADING1, fontNS::FONT_HEIGHT * 1.5, fontNS::FONT_WIDTH * 1.5, fontNS::FONT_WEIGHT, fontNS::FONT_ITALICS, fontNS::FONT_NAME);
	addFont(fontsNS::HEADING2, fontNS::FONT_HEIGHT, fontNS::FONT_WIDTH, fontNS::FONT_WEIGHT, fontNS::FONT_ITALICS, "yorkbailehill");
	addFont(fontsNS::INSTRUCTIONS, fontNS::FONT_HEIGHT / 1.5, fontNS::FONT_WIDTH / 2, fontNS::FONT_WEIGHT, fontNS::FONT_ITALICS, "instructionsFont");
	addFont(fontsNS::SUBTITLE, fontNS::FONT_HEIGHT / 2, fontNS::FONT_WIDTH / 2, fontNS::FONT_WEIGHT, true, "yorkbailehill");
	addFont(fontsNS::GAME_SELECT, fontNS::FONT_HEIGHT, fontNS::FONT_WIDTH, fontNS::FONT_WEIGHT, fontNS::FONT_ITALICS, "yorkbailehill");
	addFont(fontsNS::END_SCREEN, fontNS::FONT_HEIGHT, fontNS::FONT_WIDTH, fontNS::FONT_WEIGHT, fontNS::FONT_ITALICS, "yorkbailehill");
}

void State::assignControls(rapidjson::Document& doc)
{
	controls.insert(std::pair<Control, int>(CONTROL_UP, 0.1f));
	controls.insert(std::pair<Control, int>(CONTROL_DOWN, 0.1f));
	controls.insert(std::pair<Control, int>(CONTROL_LEFT, 0.1f));
	controls.insert(std::pair<Control, int>(CONTROL_RIGHT, 0.1f));
	controls.insert(std::pair<Control, int>(CONTROL_ENTER, 0.1f));
	controls.insert(std::pair<Control, int>(CONTROL_ESC, 0.1f));
	controls.insert(std::pair<Control, int>(CONTROL_SPACEBAR, 0.1f));

	controls.at(CONTROL_UP) = doc["state"].GetArray()[stateNS::docID]["up"].GetInt();
	controls.at(CONTROL_DOWN) = doc["state"].GetArray()[stateNS::docID]["down"].GetInt();
	controls.at(CONTROL_LEFT) = doc["state"].GetArray()[stateNS::docID]["left"].GetInt();
	controls.at(CONTROL_RIGHT) = doc["state"].GetArray()[stateNS::docID]["right"].GetInt();
	controls.at(CONTROL_ENTER) = doc["state"].GetArray()[stateNS::docID]["enter"].GetInt();
	controls.at(CONTROL_ESC) = doc["state"].GetArray()[stateNS::docID]["escape"].GetInt();
	controls.at(CONTROL_SPACEBAR) = doc["state"].GetArray()[stateNS::docID]["spacebar"].GetInt();
}

void State::addFont(fontsNS::Fonts f, int h, UINT wid, UINT wei, bool i, std::string fN)
{
	Font tempFont;

	if (!tempFont.initialize(graphics))
		throw(GameError(gameErrorNS::FATAL_ERROR, "FAILED TO INITIALIZE FONT"));

	if (!tempFont.createFont(h, wid, wei, i, fN))
		throw(GameError(gameErrorNS::FATAL_ERROR, "FAILED TO CREATE FONT"));

	fonts[f] = tempFont;
}

void State::setNextStateByInput(stateNS::NextState nS, int c)
{
		if (input->getKeyState(c))
		{
			if (!input->wasKeyPressed(c))
			{
				nextState = nS;
				pNextState = &nextState;
				input->keysPressed[c] = true;
			}
		}
		else
			input->clearKeyPress(c);
}