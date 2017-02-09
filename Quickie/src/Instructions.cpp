#include "Instructions.h"

Instructions::Instructions()
{
	currentScene = instructionsNS::MOVE_RIGHT;
	D3DXMatrixIdentity(&worldMatrix);
}

Instructions::~Instructions()
{

}

void Instructions::initialize(Graphics* g, Input* i, Audio* a, rapidjson::Document& doc, float* dT)
{
	D3DXVECTOR3 pos3D;
	State::initialize(g, i, a, doc, dT);

	graphics->camera->pointInWorld(pos3D, sqr1Pos, playerNS::z);
	sqr1 = new Player(pos3D, D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(240, 240, 0));
	graphics->camera->pointInWorld(pos3D, sqr2Pos, playerNS::z);
	sqr2 = new Player(pos3D, D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 240, 240));

	sqr1->init(g, i, a);
	sqr2->init(g, i, a);
}

void Instructions::update()
{
	UINT border = 50;
	D3DXVECTOR3 sqr1_3D;
	D3DXVECTOR3 sqr2_3D;
	
	graphics->camera->pointOnScreen(sqr1_3D, sqr1->pos);
	graphics->camera->pointOnScreen(sqr2_3D, sqr2->pos);

	if (input->getKeyState(controls.at(CONTROL_ESC)))
	{
		nextState = stateNS::REVERT;
		pNextState = &nextState;
	}
	if (input->getKeyState(controls.at(CONTROL_ENTER)))
	{
		nextState = stateNS::REVERT;
		pNextState = &nextState;
	}
	setNextStateByInput(stateNS::GAMEPLAY, controls.at(CONTROL_SPACEBAR));

	switch (currentScene)
	{
	case instructionsNS::MOVE_RIGHT:

		// move right if sqr2 not touching right screen
		if (sqr2_3D.x < GAME_WIDTH - border)
		{
			sqr1->pos.x += *deltaTime * playerNS::speed;
			sqr2->pos.x += *deltaTime * playerNS::speed;
		}
		else
			currentScene = instructionsNS::MOVE_LEFT;
		break;

	case instructionsNS::MOVE_LEFT:

		// move left if sqr 1 has not return to original position
		if (sqr1_3D.x > stateNS::sqr1X)
		{
			sqr1->pos.x -= *deltaTime * playerNS::speed;
			sqr2->pos.x -= *deltaTime * playerNS::speed;
		}

		// change scene when sqr 1 returns to original position
		else
			currentScene = instructionsNS::MOVE_UP;
		break;

	case instructionsNS::MOVE_UP:
		
		if (sqr1_3D.y > border)
		{
			sqr1->pos.y += *deltaTime * playerNS::speed;
			sqr2->pos.y += *deltaTime * playerNS::speed;
		}
		else
			currentScene = instructionsNS::MOVE_DOWN;
		break;

	case instructionsNS::MOVE_DOWN:

		if (sqr1_3D.y < stateNS::sqrY)
		{
			sqr1->pos.y -= *deltaTime * playerNS::speed;
			sqr2->pos.y -= *deltaTime * playerNS::speed;
		}
		else
			currentScene = instructionsNS::TELEPORT;
		break;

	case instructionsNS::TELEPORT:

		if (sqr1_3D.x < GAME_WIDTH / 2 && !sqr1->controlledTP)
		{
			sqr1->pos.x += *deltaTime * playerNS::speed;
		}
		else if (!sqr1->controlledTP)
		{
			sqr1->velocity.x -= *deltaTime * playerNS::speed;
			sqr1->controlledTP = true;
		}
		else if (sqr1_3D.x > border)
		{
			sqr1->pos.x -= *deltaTime * playerNS::speed;
		}
		else
		{
			sqr1->controlledTP = false;
			currentScene = instructionsNS::BLINK;
		}
		break;

	case instructionsNS::BLINK:

		if (sqr1_3D.x < GAME_WIDTH / 2)
		{
			sqr1->pos.x += *deltaTime * playerNS::speed;
		}
		else if (!sqr1->controlled)
		{
			sqr1->velocity.x += *deltaTime * playerNS::speed;
			sqr1->controlled = true;
		}
		else if (sqr1->alive)
		{
			sqr1->pos.x += *deltaTime * playerNS::speed;
		}
		else
		{
			sqr1->controlled = false;
			currentScene = instructionsNS::RESPAWN;
		}
			
		break;

	case instructionsNS::RESPAWN:

		if (sqr1->alive && sqr2->alive)
		{
			D3DXVECTOR3 pos3D;

			graphics->camera->pointInWorld(pos3D, sqr1Pos, playerNS::z);
			sqr1->pos.x = pos3D.x;
			sqr1->pos.y = pos3D.y;

			graphics->camera->pointInWorld(pos3D, sqr2Pos, playerNS::z);
			sqr2->pos.x = pos3D.x;
			sqr2->pos.y = pos3D.y;

			currentScene = instructionsNS::MOVE_RIGHT;
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

void Instructions::render()
{
	Font f, tempF;

	tempF = fonts.at(fontsNS::HEADING1);
	f = fonts.at(fontsNS::HEADING1);
	f.print(
		GAME_WIDTH / 2 - f.getTotalWidth("CONTROLS") / 2,
		f.getHeight(),
		"CONTROLS");

	f = fonts.at(fontsNS::SUBTITLE);
	f.print(GAME_WIDTH / 2 - f.getTotalWidth("press <spacebar> to skip") / 2,
		tempF.getHeight() * 2,
		"press <spacebar> to skip");

	f = fonts.at(fontsNS::HEADING2);
	f.print(
		stateNS::sqr1X - f.getTotalWidth("Player 1") / 2,
		GAME_HEIGHT / 1.5,
		fontNS::YELLOW,
		"Player 1");

	f.print(
		stateNS::sqr2X - f.getTotalWidth("Player 2") / 2,
		GAME_HEIGHT / 1.5,
		fontNS::BLUE,
		"Player 2");

	tempF = fonts.at(fontsNS::HEADING2);
	f = fonts.at(fontsNS::INSTRUCTIONS);

	switch (currentScene)
	{
	case instructionsNS::MOVE_RIGHT:
		
		f.print(
			stateNS::sqr1X - tempF.getTotalWidth("w a s D"),
			GAME_HEIGHT - tempF.getHeight() * 3,
			fontNS::YELLOW,
			"w a s D");

		f.print(
			stateNS::sqr2X - tempF.getTotalWidth("u l e R"),
			GAME_HEIGHT - tempF.getHeight() * 3,
			fontNS::BLUE,
			"u l e R");
		break;

	case instructionsNS::MOVE_LEFT:

		f.print(
			stateNS::sqr1X - tempF.getTotalWidth("w A s d"),
			GAME_HEIGHT - tempF.getHeight() * 3,
			fontNS::YELLOW,
			"w A s d");

		f.print(
			stateNS::sqr2X - tempF.getTotalWidth("u L e r"),
			GAME_HEIGHT - tempF.getHeight() * 3,
			fontNS::BLUE,
			"u L e r");
		break;

	case instructionsNS::MOVE_UP:

		f.print(
			stateNS::sqr1X - tempF.getTotalWidth("W a s d"),
			GAME_HEIGHT - tempF.getHeight() * 3,
			fontNS::YELLOW,
			"W a s d");

		f.print(
			stateNS::sqr2X - tempF.getTotalWidth("U l e r"),
			GAME_HEIGHT - tempF.getHeight() * 3,
			fontNS::BLUE,
			"U l e r");
		break;

	case instructionsNS::MOVE_DOWN:

		f.print(
			stateNS::sqr1X - tempF.getTotalWidth("w a S d"),
			GAME_HEIGHT - tempF.getHeight() * 3,
			fontNS::YELLOW,
			"w a S d");

		f.print(
			stateNS::sqr2X - tempF.getTotalWidth("u l E r"),
			GAME_HEIGHT - tempF.getHeight() * 3,
			fontNS::BLUE,
			"u l E r");
		break;

	case instructionsNS::TELEPORT:

		tempF.print(
			stateNS::sqr1X - tempF.getTotalWidth("Teleport"),
			GAME_HEIGHT - tempF.getHeight() * 4,
			"Teleport");

		f.print(
			stateNS::sqr1X - tempF.getTotalWidth("V b"),
			GAME_HEIGHT - tempF.getHeight() * 3,
			fontNS::YELLOW,
			"V b");

		tempF.print(
			stateNS::sqr2X - tempF.getTotalWidth("Teleport"),
			GAME_HEIGHT - tempF.getHeight() * 4,
			"Teleport");

		f.print(
			stateNS::sqr2X - tempF.getTotalWidth("C f"),
			GAME_HEIGHT - tempF.getHeight() * 3,
			fontNS::BLUE,
			"C f");
		break;

	case instructionsNS::BLINK:

		tempF.print(
			stateNS::sqr1X + tempF.getTotalWidth("Blink") / 2,
			GAME_HEIGHT - tempF.getHeight() * 4,
			"Blink");

		f.print(
			stateNS::sqr1X - tempF.getTotalWidth("v B"),
			GAME_HEIGHT - tempF.getHeight() * 3,
			fontNS::YELLOW,
			"v B");

		tempF.print(
			stateNS::sqr2X + tempF.getTotalWidth("Blink") / 2,
			GAME_HEIGHT - tempF.getHeight() * 4,
			"Blink");

		f.print(
			stateNS::sqr2X - tempF.getTotalWidth("c F"),
			GAME_HEIGHT - tempF.getHeight() * 3,
			fontNS::BLUE,
			"c F");
		break;

	case instructionsNS::RESPAWN:

		f = fonts.at(fontsNS::HEADING2);

		f.print(
			GAME_WIDTH / 2 - f.getTotalWidth("Do not touch the line or the borders!") / 2,
			GAME_HEIGHT - tempF.getHeight() * 3,
			fontNS::RED,
			"Do not touch the line or the borders!");
		break;
	}

	for (int i = 0; i < qEnvironmentObj.size(); i++) {
		qEnvironmentObj[i]->draw(worldMatrix);
	}
	sqr1->draw(worldMatrix);
	sqr2->draw(worldMatrix);
}
