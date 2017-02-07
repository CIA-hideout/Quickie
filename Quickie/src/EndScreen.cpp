#include "EndScreen.h"

EndScreen::EndScreen()
{
	D3DXMatrixIdentity(&worldMatrix);
}

EndScreen::~EndScreen()
{
	
}

void EndScreen::initialize(Graphics* g, Input* i, Audio* a, rapidjson::Document& doc)
{
	State::initialize(g, i, a, doc);
}

void EndScreen::update()
{
	
}

void EndScreen::render()
{
	Font f;

	f = fonts.at(MENU_TITLE);

	// Set Title Screen
	if (winnerID == 0)
	{
		f.print(
			GAME_WIDTH / 2 - f.getTotalWidth("GAME OVER") / 2,
			GAME_HEIGHT / 5,
			"Player 1 wins");	
	}
	else
	{
		f.print(
			GAME_WIDTH / 2 - f.getTotalWidth("GAME OVER") / 2,
			GAME_HEIGHT / 5,
			"Player 2 wins");
	}

	// Set Fonts for Options
	f = fonts.at(END_SCREEN);
	int offSetY = 0;
	

	f.print(
		GAME_WIDTH / 2 - f.getTotalWidth(("> " + endscreenNS::options[i])) / 2,
		GAME_HEIGHT / 2 + offSetY,
		"> " + endscreenNS::options[i]);
}

void EndScreen::setWinner(std::vector<VertexShape*> players)			// get Winner of the game
{
	for (int i = 0; i < players.size(); i++)
	{
		Player* tempPlayer = (Player*)players[i];
		if (tempPlayer->isWinner)
			winnerID = i;
	}
}