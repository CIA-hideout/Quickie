#include "Menu.h"

Menu::Menu()
{
};


Menu::~Menu(){};

void Menu::initialize(Graphics* g, Input* i, Audio* a , rapidjson::Document& doc, float* dT)
{
	State::initialize(g, i, a, doc, dT);
}


void Menu::update()
{
	setNextStateByInput(stateNS::INSTRUCTIONS, controls.at(CONTROL_SPACEBAR));
}

void Menu::render()
{
	Font f;

	f = fonts.at(fontsNS::HEADING1);

	f.print(
		GAME_WIDTH / 2 - f.getTotalWidth("QUICKIE") / 2,
		GAME_HEIGHT / 5,
		"QUICKIE");

	f = fonts.at(fontsNS::HEADING2);

	if (timeGetTime() % 500 < 250)
	{
		f.print(
			GAME_WIDTH / 2 - f.getTotalWidth("[PRESS SPACE TO PLAY]") / 2,
			GAME_HEIGHT / 2,
			"[PRESS SPACE TO PLAY]");
	}
}