#include "Instructions.h"

Instructions::Instructions()
{
	D3DXMatrixIdentity(&worldMatrix);
}

Instructions::~Instructions()
{
	
}

void Instructions::initialize(Graphics* g, Input* i)
{
	sqr1->init(g, i);
	sqr2->init(g, i);
	State::initialize(g, i);
}

void Instructions::update()
{
	std::vector<VertexShape*> tempVector = {sqr1};

	if (input->getKeyState(controls.at(CONTROL_RIGHT)))
	{
		nextState = stateNS::GAMEPLAY;
		pNextState = &nextState;
	}
	if (input->getKeyState(controls.at(CONTROL_LEFT)))
	{
		nextState = stateNS::REVERT;
		pNextState = &nextState;
	}

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
