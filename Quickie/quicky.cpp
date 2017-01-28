#include "quicky.h"
#include <math.h>

Obstacle* o1 = new Obstacle(D3DXVECTOR3(0, 3, 20), D3DXVECTOR3(10, 0.5, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 0, 255));
Obstacle* o2 = new Obstacle(D3DXVECTOR3(-5, 0, 20), D3DXVECTOR3(1.5, 20, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 0, 255));
Obstacle* o3 = new Obstacle(D3DXVECTOR3(0, -5, 20), D3DXVECTOR3(10, 0.5, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 0, 255));
Obstacle* o4 = new Obstacle(D3DXVECTOR3(5, 0, 20), D3DXVECTOR3(1.5, 20, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 0, 255));

Player* sqr = new Player(D3DXVECTOR3(0, 0, 20), D3DXVECTOR3(1.5, 1.5, 1.5), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 255, 255));

std::vector<VertexShape*> obs;

quicky::quicky() {

}

quicky::~quicky() {

}

void quicky::initialize(HWND hWnd) {

	Game::initialize(hWnd);

	o3->collisionType = CT_AABB;
	sqr->collisionType = CT_AABB;

	o1->init(this);
	o2->init(this);
	o3->init(this);
	o4->init(this);
	sqr->init(this);

	this->input = new Input(this->hwnd);

	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);

	cManager = new CollisionManager();
	
	obs.push_back(o1);
	obs.push_back(o2);
	obs.push_back(o3);
	obs.push_back(o4);
	obs.push_back(sqr);

}

void quicky::update() {

	o1->update(deltaTime);
	o2->update(deltaTime);
	o3->update(deltaTime);
	o4->update(deltaTime);

	sqr->update(deltaTime, obs);

}

void quicky::ai() {

}

void quicky::collisions() {

}

void quicky::render() {

	sqr->draw(worldMat);
	o1->draw(worldMat);
	o2->draw(worldMat);
	o3->draw(worldMat);
	o4->draw(worldMat);

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

	// printf("%.2f, %.2f\n", deltax, deltay);

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

	if (key == DIK_LEFT) {
		sqr->velocity.x -= deltaTime * 10 / ASPECT_RATIO;
	}

	if (key == DIK_RIGHT) {
		sqr->velocity.x += deltaTime * 10 / ASPECT_RATIO;
	}

	if (key == DIK_UP) {
		sqr->velocity.y += deltaTime * 10;
	}

	if (key == DIK_DOWN) {
		sqr->velocity.y -= deltaTime * 10;
	}

	if (key == DIK_SPACE && sqr->cooldown.at(COOLDOWN_TELEPORT) <= 0.0f) {
		if (input->getKeyState(DIK_UP)) {
			sqr->velocity = sqr->velocity * 0;
			sqr->pos.y += 10;
		}
		if (input->getKeyState(DIK_LEFT)) {
			sqr->velocity = sqr->velocity * 0;
			sqr->pos.x -= 10;
		}
		if (input->getKeyState(DIK_RIGHT)) {
			sqr->velocity = sqr->velocity * 0;
			sqr->pos.x += 10;
		}
		sqr->cooldown.at(COOLDOWN_TELEPORT) = 2.0f;
	}

	if (key == DIK_R) {

		sqr->pos.x = 0;
		sqr->pos.y = 0;
		sqr->pos.z = 20;

		sqr->velocity *= 0;
	}

}

void quicky::keyRelease(int key) {

}

void quicky::mouseButton(int key) {

}

void quicky::mouseButtonRelease(int key) {

}

void quicky::mouseMove(int x, int y) {

}
