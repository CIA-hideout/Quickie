#include "quicky.h"

LTriangle* lt = new LTriangle();
LSquare* ls = new LSquare();

quicky::quicky() {

}

quicky::~quicky() {

}

void quicky::initialize(HWND hWnd) {

	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);

	Game::initialize(hWnd);

	lt->init(this);
	ls->init(this);
}

void quicky::update() {
	lt->update(deltaTime);
	ls->update(deltaTime);
}

void quicky::ai() {

}

void quicky::collisions() {

}

void quicky::render() {

	graphics->get3Ddevice()->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	graphics->get3Ddevice()->BeginScene();
	graphics->get3Ddevice()->SetFVF(CUSTOMFVF);

	// lt->draw(deltaTime);
	ls->draw(deltaTime);

	graphics->get3Ddevice()->EndScene();
	graphics->get3Ddevice()->Present(NULL, NULL, NULL, NULL);

}

void quicky::releaseAll() {

}

void quicky::resetAll() {

}
