#include "quicky.h"

Obstacle* o1 = new Obstacle(D3DXVECTOR3(0, 5, 20 - 0.5), D3DXVECTOR3(10, 1.5, 0.5), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 0, 255));
Obstacle* o2 = new Obstacle(D3DXVECTOR3(-5, 0, 20 - 0.5), D3DXVECTOR3(1.5, 10, 0.5), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 0, 255));
Obstacle* o3 = new Obstacle(D3DXVECTOR3(0, -5, 20 - 0.5), D3DXVECTOR3(10, 1.5, 0.5), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 0, 255));
Obstacle* o4 = new Obstacle(D3DXVECTOR3(5, 0, 20 - 0.5), D3DXVECTOR3(1.5, 10, 0.5), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 0, 255));

Player* sqr1 = new Player(D3DXVECTOR3(0, 0, 20 - 1), D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 255, 255));
Player* sqr2 = new Player(D3DXVECTOR3(10, 10, 20 - 1), D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 240, 240));

quicky::quicky() {

}

quicky::~quicky() {

}

void quicky::initialize(HWND hWnd) {

	Game::initialize(hWnd);

	this->input = new Input(this->hwnd);

	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);

	vEntities.push_back(o1);
	vEntities.push_back(o2);
	vEntities.push_back(o3);
	vEntities.push_back(o4);


	// Font initialization
	font = new FontHandler();

	if (!font->initialize(graphics))
		throw(GameError(gameErrorNS::FATAL_ERROR, "FAIL TO INITIALIZE FONT"));

	if (!font->createFont(FONT_HEIGHT, FONT_WIDTH, FONT_WEIGHT, FONT_ITALICS, FONT_NAME))					// height, width, weight, italics, Font Name
		throw(GameError(gameErrorNS::FATAL_ERROR, "FAIL TO CREATE FONT"));

	// GUI initialization
	gui = new GUI();

	if (!gui->initialize(font))
		throw(GameError(gameErrorNS::FATAL_ERROR, "FAIL TO INITIALIZE GUI"));


	// parse player control
	FILE* controlFile = fopen("resource\\data\\control.json", "rb");
	char controlBuffer[512];
	rapidjson::FileReadStream is(controlFile, controlBuffer, sizeof(controlBuffer));

	controlDoc.ParseStream(is);
	printf("%s\n", controlDoc["test_string"].GetString());

	o1->init(this);
	o2->init(this);
	o3->init(this);
	o4->init(this);
	sqr1->init(this);
	sqr2->init(this);

	sqr1->assignControl(controlDoc);
	sqr2->assignControl(controlDoc);
	fclose(controlFile);
}

void quicky::update() {

	for (int i = 0; i < vEntities.size(); i++) {
		vEntities[i]->update(deltaTime);
	}

	sqr1->update(deltaTime, vEntities);
	sqr2->update(deltaTime, vEntities);

}

void quicky::ai() {

}

void quicky::collisions() {

}

void quicky::render() {

	for (int i = 0; i < vEntities.size(); i++) {
		vEntities[i]->draw(worldMat);
	}
	sqr1->draw(worldMat);
	sqr2->draw(worldMat);

	gui->render();
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

	if (key == DIK_SPACE) {
		if (sqr1->cooldown.at(COOLDOWN_BLINK) <= 0) {
			sqr1->blink(vEntities);
		}
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
