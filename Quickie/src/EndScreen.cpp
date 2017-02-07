#include "EndScreen.h"

EndScreen::EndScreen()
{
	D3DXMatrixIdentity(&worldMatrix);
}

EndScreen::~EndScreen()
{
	
}

void EndScreen::initialize(Graphics* g, Input* i, Audio* a, rapidjson::Document& doc, float* dT)
{
	deltaTime = dT;
	State::initialize(g, i, a, doc);
}

void EndScreen::update()
{
	if (input->getKeyState(controls.at(CONTROL_ENTER)))
	{
		nextState = stateNS::REVERT;
		pNextState = &nextState;
	}
}

void EndScreen::render()
{
	Font f;

	f = fonts.at(fontsNS::HEADING1);

	Player temp = Player(D3DXVECTOR3(0, 0, 20 - 1), D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(240, 240, 0));
	// Set Title Screen
	if (temp.winner == 1)
	{
		f.print(
			GAME_WIDTH / 2 - f.getTotalWidth("GAME OVER") / 2,
			GAME_HEIGHT / 5,
			fontNS::YELLOW,
			"Player 1 wins");	
	}
	else if (temp.winner == 2)
	{
		f.print(
			GAME_WIDTH / 2 - f.getTotalWidth("GAME OVER") / 2,
			GAME_HEIGHT / 5,
			fontNS::BLUE,
			"Player 2 wins");
	}

	// Set Fonts for Options
	f = fonts.at(fontsNS::END_SCREEN);
	
	f.print(
		GAME_WIDTH / 2 - f.getTotalWidth(("> Return")) / 2,
		GAME_HEIGHT / 2,
		"> Return");
}