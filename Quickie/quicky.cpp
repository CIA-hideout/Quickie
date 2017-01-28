#include "quicky.h"
#include <math.h>

Obstacle* o1 = new Obstacle(D3DXVECTOR3(0, 5, 20 - 2.5), D3DXVECTOR3(10, 1.5, 5), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 0, 255));
Obstacle* o2 = new Obstacle(D3DXVECTOR3(-5, 0, 20 - 2.5), D3DXVECTOR3(1.5, 10, 5), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 0, 255));
Obstacle* o3 = new Obstacle(D3DXVECTOR3(0, -5, 20 - 2.5), D3DXVECTOR3(10, 1.5, 5), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 0, 255));
Obstacle* o4 = new Obstacle(D3DXVECTOR3(5, 0, 20 - 2.5), D3DXVECTOR3(1.5, 10, 5), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 0, 255));
Obstacle o8 = Obstacle(SPAWN_LEFT);
Obstacle o9 = Obstacle(SPAWN_CENTER);
Obstacle o10 = Obstacle(SPAWN_RIGHT);

Player* sqr1 = new Player(D3DXVECTOR3(0, 0, 20 - 1), D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 255, 255));
Player* sqr2 = new Player(D3DXVECTOR3(10, 10, 20 - 1), D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 240, 240));

std::vector<VertexShape*> obs;
std::vector<Obstacle> obs_test;

quicky::quicky() {
	obs_test.push_back(o8);
	obs_test.push_back(o9);
	obs_test.push_back(o10);
}

quicky::~quicky() {

}

void quicky::initialize(HWND hWnd) {

	Game::initialize(hWnd);

	o1->init(this);
	o2->init(this);
	o3->init(this);
	o4->init(this);
	sqr1->init(this);
	sqr2->init(this);

	this->input = new Input(this->hwnd);

	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);

	obs.push_back(o1);
	obs.push_back(o2);
	obs.push_back(o3);
	obs.push_back(o4);

	//Implement basic font support
	font = new FontHandler();

	if (!font->initialize(graphics))
		throw(GameError(gameErrorNS::FATAL_ERROR, "FAIL TO INITIALIZE FONT"));

	if (!font->createFont(FONT_HEIGHT, FONT_WIDTH, FONT_WEIGHT, FONT_ITALICS, FONT_NAME))					// height, width, weight, italics, Font Name
		throw(GameError(gameErrorNS::FATAL_ERROR, "FAIL TO CREATE FONT"));
}

void quicky::update() {

	for (int i = 0; i < obs.size(); i++) {
		obs[i]->update(deltaTime);
	}

	sqr1->update(deltaTime, obs);
	sqr2->update(deltaTime, obs);

}

void quicky::ai() {

}

void quicky::collisions() {

}

void quicky::render() {

	for (int i = 0; i < obs.size(); i++) {
		obs[i]->draw(worldMat);
	}
	sqr1->draw(worldMat);
	sqr2->draw(worldMat);

	// font->print(500, 500, "AIR AMERICANA");
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

	if (key == DIK_LEFT) {
		sqr1->velocity.x -= deltaTime * 10 / ASPECT_RATIO;
	}

	if (key == DIK_RIGHT) {
		sqr1->velocity.x += deltaTime * 10 / ASPECT_RATIO;
	}

	if (key == DIK_UP) {
		sqr1->velocity.y += deltaTime * 10;
	}

	if (key == DIK_DOWN) {
		sqr1->velocity.y -= deltaTime * 10;
	}
	if (key == DIK_A) {
		sqr2->velocity.x -= deltaTime * 10 / ASPECT_RATIO;
	}

	if (key == DIK_D) {
		sqr2->velocity.x += deltaTime * 10 / ASPECT_RATIO;
	}

	if (key == DIK_W) {
		sqr2->velocity.y += deltaTime * 10;
	}

	if (key == DIK_S) {
		sqr2->velocity.y -= deltaTime * 10;
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
