#include "quicky.h"

]Obstacle o3 = Obstacle(D3DXVECTOR3(0, 0, 20), D3DXVECTOR3(10, 1, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 0, 255));
Player* sqr = new Player(D3DXVECTOR3(0, 5, 20), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 255, 255));

Obstacle* o8 = new Obstacle(D3DXVECTOR3(0, 10, 8));


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

	o3.collisionType = COLLISION_TYPE_BOUNDING_BOX;
	sqr->collisionType = COLLISION_TYPE_BOUNDING_BOX;

	o3.init(this);

	sqr->init(this);

	o8->init(this);
}

void quicky::update() {

	o3.update(deltaTime);
	sqr->update(deltaTime);

	if (sqr->onPlatform == false) {
		sqr->velocity.y += deltaTime * -9.81 / 200;
		sqr->pos += sqr->velocity;
	}

	sqr->rotation.y += 0.01;

	o8->update(deltaTime);

}

void quicky::ai() {

}

void quicky::collisions() {
	printf("%.2f, %.2f | %.2f\n", sqr->pos.y, sqr->max.y, o3.pos.y);
	if (sqr->collidesWith(o3)) {
		// printf("%.2f, %.2f | %.2f\n", sqr->pos.y, sqr->max.y, o3.pos.y);
		sqr->velocity.y = 0;
		sqr->pos.y = o3.max.y + (sqr->max.y - sqr->min.y) / 2;
		sqr->onPlatform = true;
	}

}

void quicky::render() {

	sqr->draw(worldMat);
	o3.draw(worldMat);

	o8->draw();

}

void quicky::releaseAll() {
	FreeConsole();
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
