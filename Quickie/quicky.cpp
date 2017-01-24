#include "quicky.h"

//Obstacle o3 = Obstacle(D3DXVECTOR3(0, 0, 20), D3DXVECTOR3(10, 1, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 0, 255));
Player* sqr = new Player(D3DXVECTOR3(0, 5, 20), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 255, 255));

Obstacle o8 = Obstacle(SPAWN_LEFT);
Obstacle o9 = Obstacle(SPAWN_CENTER);
Obstacle o1 = Obstacle(SPAWN_RIGHT);
std::vector<Obstacle> obs;

quicky::quicky() {
	obs.push_back(o8);
	obs.push_back(o9);
	obs.push_back(o1);
}

quicky::~quicky() {

}

void quicky::initialize(HWND hWnd) {

	Game::initialize(hWnd);

	//o3.collisionType = CT_AABB;
	sqr->collisionType = CT_AABB;

	//o3.init(this);
	sqr->init(this);

	//o1.init(this);
	//o8.init(this);
	//o9.init(this);

	for (std::vector<Obstacle>::iterator i = obs.begin(); i != obs.end(); i++)
		i->init(this);

	this->input = new Input(this->hwnd);

	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);
}

void quicky::update() {

	
	//o3.update(deltaTime);
	sqr->update(deltaTime);

	if (sqr->onPlatform == nullptr) {
		sqr->velocity.y += deltaTime * -9.81 / 200;
		sqr->pos += sqr->velocity;
	}
	for (std::vector<Obstacle>::iterator i = obs.begin(); i != obs.end(); i++)
		i->update(deltaTime);

	//o1.update(deltaTime);
	//o8.update(deltaTime);
	//o9.update(deltaTime);

	//o3.pos.y -= 0.01f;
	
	
}

void quicky::ai() {

}

void quicky::collisions() {
	/*
	// printf("%.2f, %.2f | %.2f\n", sqr->pos.y, sqr->max.y, o3.pos.y);
	if (sqr->collidesWith(o3)) {
		sqr->velocity.y = 0;
		if (sqr->pos.y > o3.pos.y) {
			sqr->pos.y = o3.max.y + (sqr->max.y - sqr->min.y) / 2;
			sqr->onPlatform = &o3;
			sqr->canJump = true;
		}
	}
	*/
	int counter = 0;
	for (std::vector<Obstacle>::iterator i = obs.begin(); i != obs.end(); ++i)
	{
		Obstacle temp = Obstacle(*i);
		
		if (sqr->collidesWith(temp)) {
			sqr->velocity.y = 0;
			if (sqr->pos.y > temp.pos.y) {
				sqr->pos.y = temp.max.y + (sqr->max.y - sqr->min.y) / 2;
				sqr->onPlatform = &obs.at(counter);
				sqr->canJump = true;
				printf("MAX: %.2f, POS: %.2f\n", temp.max.y, temp.pos.y);
				printf("Player: %.2f\n", sqr->pos.y);
			}
		}
		//printf("%.2f\n", sqr->pos.y);
		counter++;
	}
	
	

	/*
	if (sqr->collidesWith(o1)) {
		sqr->velocity.y = 0;
		if (sqr->pos.y > o1.pos.y) {
			sqr->pos.y = o1.max.y + (sqr->max.y - sqr->min.y) / 2;
			sqr->onPlatform = &o1;
			sqr->canJump = true;
		}
	}

	if (sqr->collidesWith(o8)) {
		sqr->velocity.y = 0;
		if (sqr->pos.y > o8.pos.y) {
			sqr->pos.y = o8.max.y + (sqr->max.y - sqr->min.y) / 2;
			sqr->onPlatform = &o8;
			sqr->canJump = true;
		}
	}

	if (sqr->collidesWith(o9)) {
		sqr->velocity.y = 0;
		if (sqr->pos.y > o9.pos.y) {
			sqr->pos.y = o9.max.y + (sqr->max.y - sqr->min.y) / 2;
			sqr->onPlatform = &o9;
			sqr->canJump = true;
		}
	}
	*/
	
	
}

void quicky::render() {
	
	sqr->draw(worldMat);
	//o3.draw(worldMat);
	
	for (std::vector<Obstacle>::iterator i = obs.begin(); i != obs.end(); i++)
		i->draw(worldMat);

	//o1.draw(worldMat);
	//o8.draw(worldMat);
	//o9.draw(worldMat);
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

	//printf("%.2f, %.2f\n", deltax, deltay);

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
		sqr->pos.x -= 10 * deltaTime;
	}

	if (key == DIK_RIGHT) {
		sqr->pos.x += 10 * deltaTime;
	}

	if (key == DIK_UP && sqr->canJump == true) {
		sqr->velocity.y += 10 * deltaTime;
		sqr->canJump = false;
		sqr->onPlatform = nullptr;
	}
	
}

void quicky::keyRelease(int key) {

}

void quicky::mouseButton(int key) {

}

void quicky::mouseButtonRelease(int key) {

}

void quicky::mouseMove(int x, int y) {
	//printf("%.2f, %.2f\n", x, y);
}
