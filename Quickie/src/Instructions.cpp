#include "Instructions.h"

Instructions::Instructions()
{
	D3DXMatrixIdentity(&worldMatrix);
}

Instructions::~Instructions()
{
	
}

void Instructions::initialize(Graphics* g, Input* i, Audio* a, rapidjson::Document& doc)
{
	State::initialize(g, i, a, doc);
	sqr1->init(g, i);
	sqr1->setLocked(true);
	sqr2->init(g, i);
	sqr2->setLocked(true);
}

void Instructions::update()
{
	std::vector<VertexShape*> tempVector = {sqr1};

	setNextStateByInput(stateNS::REVERT, controls.at(CONTROL_ESC));
	setNextStateByInput(stateNS::GAMEPLAY, controls.at(CONTROL_RIGHT));

	if (blink)
	{
		float r;
		r = atan(sqr1->velocity.y / sqr1->velocity.x);
		sqr1->blink(tempVector, r);
		blink = false;
	}
}

void Instructions::render()
{
	Font f;

	f = fonts.at(MENU_TITLE);

	f.print(
		GAME_WIDTH / 2 - f.getTotalWidth("Press something to blink.") / 2,
		GAME_HEIGHT / 5,
		"Press something to blink.");

	sqr1->draw(worldMatrix);
	sqr2->draw(worldMatrix);
}
