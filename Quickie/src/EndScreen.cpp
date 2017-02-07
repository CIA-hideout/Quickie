#include "EndScreen.h"

EndScreen::EndScreen()
{
	currentScene = endscreenNS::EXPLODE;
	D3DXMatrixIdentity(&worldMatrix);
}

EndScreen::~EndScreen()
{
	
}

void EndScreen::initialize(Graphics* g, Input* i, Audio* a, rapidjson::Document& doc, float* dT)
{
	D3DXVECTOR3 pos3D;
	State::initialize(g, i, a, doc, dT);
	Player temp = Player();

	graphics->camera->pointInWorld(pos3D, sqr1Pos, endscreenNS::z);
	if (temp.winner == 1)
		sqr1 = new Player(pos3D, D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(240, 240, 0));
	else
		sqr1 = new Player(pos3D, D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 240, 240));
	graphics->camera->pointInWorld(pos3D, sqr2Pos, endscreenNS::z);
	if (temp.winner == 2)
		sqr2 = new Player(pos3D, D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 240, 240));
	else
		sqr2 = new Player(pos3D, D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(240, 240, 0));

	sqr1->init(g, i);
	sqr2->init(g, i);
	State::initialize(g, i, a, doc, dT);
}

void EndScreen::update()
{
	if (input->getKeyState(controls.at(CONTROL_ENTER)))
	{
		nextState = stateNS::REVERT;
		pNextState = &nextState;
	}
	else
	{
		switch (currentScene)
		{
		case endscreenNS::EXPLODE:
			sqr1->velocity.x -= *deltaTime * endscreenNS::speed;
			sqr1->controlled = true;
			sqr2->velocity.x += *deltaTime * endscreenNS::speed;
			sqr2->controlled = true;
			currentScene = endscreenNS::RESPAWN;
			break;

		case endscreenNS::RESPAWN:
			if (sqr1->alive && sqr2->alive)
			{
				D3DXVECTOR3 pos3D;

				graphics->camera->pointInWorld(pos3D, sqr1Pos, endscreenNS::z);
				sqr1->pos.x = pos3D.x;
				sqr1->pos.y = pos3D.y;
				sqr1->health++;

				graphics->camera->pointInWorld(pos3D, sqr2Pos, endscreenNS::z);
				sqr2->pos.x = pos3D.x;
				sqr2->pos.y = pos3D.y;
				sqr2->health++;
				
				currentScene = endscreenNS::EXPLODE;
			}
			break;
		}
		
		graphics->camera->update(*deltaTime);
		sqr1->update(*deltaTime, qEnvironmentObj);
		sqr2->update(*deltaTime, qEnvironmentObj);

		for (int i = 0; i < qEnvironmentObj.size(); ++i)
		{
			if (qEnvironmentObj[i]->objectType == OBJECT_TYPE_QLINE) {
				QLine* temp = (QLine*)qEnvironmentObj[i];
				temp->update(*deltaTime, qEnvironmentObj);
			}
		}
	}
}

void EndScreen::render()
{
	Font f;

	f = fonts.at(fontsNS::HEADING1);
	
	// Set Title Screen
	if (sqr1->winner == 1)
	{
		f.print(
			GAME_WIDTH / 2 - f.getTotalWidth("GAME OVER") / 2,
			GAME_HEIGHT / 5,
			fontNS::YELLOW,
			"Player 1 wins");	
	}
	else if (sqr2->winner == 2)
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

	for (int i = 0; i < qEnvironmentObj.size(); i++) {
		qEnvironmentObj[i]->draw(worldMatrix);
	}
	sqr1->draw(worldMatrix);
	sqr2->draw(worldMatrix);
}