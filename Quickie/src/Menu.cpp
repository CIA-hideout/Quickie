#include "Menu.h"

Menu::Menu()
{
	currentScene = menuNS::BLINK;
	D3DXMatrixIdentity(&worldMatrix);
};


Menu::~Menu(){};

void Menu::initialize(Graphics* g, Input* i, Audio* a , rapidjson::Document& doc, float* dT)
{
	State::initialize(g, i, a, doc, dT);

	D3DXVECTOR3 pos3D;

	graphics->camera->pointInWorld(pos3D, sqr1Pos, playerNS::z);
	sqr1 = new Player(pos3D, D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(240, 240, 0));
	graphics->camera->pointInWorld(pos3D, sqr2Pos, playerNS::z);
	sqr2 = new Player(pos3D, D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 240, 240));

	sqr1->init(g, i, a);
	sqr2->init(g, i, a);
}


void Menu::update()
{
	setNextStateByInput(stateNS::INSTRUCTIONS, controls.at(CONTROL_SPACEBAR));

	if (canPlaySound) {
		// audio->playCue(menuBGM);
		canPlaySound = false;
	}

	switch (currentScene)
	{
	case menuNS::BLINK:
		sqr1->velocity.x += *deltaTime * playerNS::speed;
		sqr1->controlledTP = true;
		sqr2->velocity.x -= *deltaTime * playerNS::speed;
		sqr2->controlledTP = true;
		currentScene = menuNS::BLINK_OPPOSITE;
		break;

	case menuNS::BLINK_OPPOSITE:
		if (sqr1->alive && sqr2->alive)
		{
			sqr1->velocity.x -= *deltaTime * playerNS::speed;
			sqr2->velocity.x += *deltaTime * playerNS::speed;
			
			currentScene = menuNS::BLINK;
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

	for (int i = 0; i < qEnvironmentObj.size(); i++) {
		qEnvironmentObj[i]->draw(worldMatrix);
	}
	sqr1->draw(worldMatrix);
	sqr2->draw(worldMatrix);
}