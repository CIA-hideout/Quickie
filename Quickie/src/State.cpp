#include "State.h"

State::State()
{
	input = nullptr;
	fonts = std::map<Fonts, Font>();
	graphics = nullptr;
	pNextState = nullptr;
};


State::~State(){};

void State::initialize(Graphics* g, Input* i)
{
	graphics = g;
	input = i;
	initFonts();

	controls.insert(std::pair<Control, int>(CONTROL_UP, 0.1f));
	controls.insert(std::pair<Control, int>(CONTROL_DOWN, 0.1f));
	controls.insert(std::pair<Control, int>(CONTROL_LEFT, 0.1f));
	controls.insert(std::pair<Control, int>(CONTROL_RIGHT, 0.1f));
}

void State::initFonts()
{
	addFont(DEFAULT, fontNS::FONT_HEIGHT, fontNS::FONT_WIDTH, fontNS::FONT_WEIGHT, fontNS::FONT_ITALICS, fontNS::FONT_NAME);
	addFont(MENU_TITLE, fontNS::FONT_HEIGHT * 1.5, fontNS::FONT_WIDTH * 1.5, fontNS::FONT_WEIGHT, fontNS::FONT_ITALICS, fontNS::FONT_NAME);
	addFont(MENU_OPTIONS, fontNS::FONT_HEIGHT, fontNS::FONT_WIDTH, fontNS::FONT_WEIGHT, fontNS::FONT_ITALICS, "yorkbailehill");
	addFont(GAME, fontNS::FONT_HEIGHT / 2, fontNS::FONT_WIDTH / 20, fontNS::FONT_WEIGHT / 5, fontNS::FONT_ITALICS, "HeartFont");
}

void State::initControls(rapidjson::Document& doc)
{
	controls.at(CONTROL_UP) = doc["control"].GetArray()[0]["up"].GetInt();
	controls.at(CONTROL_DOWN) = doc["control"].GetArray()[0]["down"].GetInt();
	controls.at(CONTROL_LEFT) = doc["control"].GetArray()[0]["left"].GetInt();
	controls.at(CONTROL_RIGHT) = doc["control"].GetArray()[0]["right"].GetInt();
}

void State::addFont(Fonts f, int h, UINT wid, UINT wei, bool i, std::string fN)
{
	Font tempFont;

	if (!tempFont.initialize(graphics))
		throw(GameError(gameErrorNS::FATAL_ERROR, "FAILED TO INITIALIZE FONT"));

	if (!tempFont.createFont(h, wid, wei, i, fN))
		throw(GameError(gameErrorNS::FATAL_ERROR, "FAILED TO CREATE FONT"));

	fonts[f] = tempFont;
}