#include "quicky.h"

LSquare* ls = new LSquare();
Obstacle* o1 = new Obstacle(D3DXVECTOR3(4, -4, 10), D3DXVECTOR3(10, 1, 1), D3DXVECTOR3(1, 1, 1));
Obstacle* o2 = new Obstacle(D3DXVECTOR3(-4, -4, 10), D3DXVECTOR3(10, 1, 1), D3DXVECTOR3(1, 1, 1));
Obstacle* o3 = new Obstacle(D3DXVECTOR3(0, 0, 10), D3DXVECTOR3(10, 1, 1), D3DXVECTOR3(1, 1, 1));
Obstacle* o4 = new Obstacle(D3DXVECTOR3(4, 4, 10), D3DXVECTOR3(10, 1, 1), D3DXVECTOR3(1, 1, 1));
Obstacle* o5 = new Obstacle(D3DXVECTOR3(-4, 4, 10), D3DXVECTOR3(10, 1, 1), D3DXVECTOR3(1, 1, 1));
Obstacle* o6 = new Obstacle(D3DXVECTOR3(8, 0, 10), D3DXVECTOR3(7, 1, 1), D3DXVECTOR3(1, 1, 1));
Obstacle* o7 = new Obstacle(D3DXVECTOR3(-8, 0, 10), D3DXVECTOR3(7, 1, 1), D3DXVECTOR3(1, 1, 1));

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

	// ls->init(this);
	o1->init(this);
	o2->init(this);
	o3->init(this);
	o4->init(this);
	o5->init(this);
	o6->init(this);
	o7->init(this);
}

void quicky::update() {

	// ls->update(deltaTime);
	o1->update(deltaTime);
	o2->update(deltaTime);
	o3->update(deltaTime);
	o4->update(deltaTime);
	o5->update(deltaTime);
	o6->update(deltaTime);
	o7->update(deltaTime);

	input->update();
	updateMouse();
	updateKeyboard();
}

void quicky::ai() {

}

void quicky::collisions() {

}

void quicky::render() {

	static float someCount = 0.0f;

	// 20 units away from the origin
	o1->draw();
	o2->draw();
	o3->draw();
	o4->draw();
	o5->draw();
	o6->draw();
	o7->draw();
	// teapot->DrawSubset(0);

}

void quicky::releaseAll() {

}

void quicky::resetAll() {

}

void quicky::updateMouse() {
	static int oldPosX = 0;
	static int oldPosY = 0;
	int deltax = input->GetDeltaX();
	int deltay = input->GetDeltaY();

	//check mouse buttons
	for (int n = 0; n < 4; n++)
	{
		if (input->getMouseButton(n))
			mouseButton(n);
	}

	//check mouse position
	if (input->GetPosX() != oldPosX || input->GetPosY() != oldPosY) {
		mouseMove(input->GetPosX(), input->GetPosY());
		oldPosX = input->GetPosX();
		oldPosY = input->GetPosY();
	}
}

void quicky::updateKeyboard() {
	static char old_keys[256];

	for (int n = 0; n < 255; n++) {
		//check for key press
		if (input->getKeyState(n) & 0x80) {
			keyPress(n);
			old_keys[n] = input->getKeyState(n);
		}
		//check for release
		else if (old_keys[n] & 0x80) {
			keyRelease(n);
			old_keys[n] = input->getKeyState(n);
		}
	}
}

void quicky::keyPress(int key) {

}

void quicky::keyRelease(int key) {

}

void quicky::mouseButton(int key) {

}

void quicky::mouseButtonRelease(int key) {

}

void quicky::mouseMove(int x, int y) {

}
