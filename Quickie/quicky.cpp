#include "quicky.h"

Obstacle* o1 = new Obstacle(D3DXVECTOR3(0, 10, 20 - 0.5), D3DXVECTOR3(10, 1.5, 0.5), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 0, 255));
Obstacle* o2 = new Obstacle(D3DXVECTOR3(-5, 0, 20 - 0.5), D3DXVECTOR3(1.5, 10, 0.5), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 0, 255));
Obstacle* o3 = new Obstacle(D3DXVECTOR3(0, -10, 20 - 0.5), D3DXVECTOR3(10, 1.5, 0.5), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 0, 255));
Obstacle* o4 = new Obstacle(D3DXVECTOR3(5, 0, 20 - 0.5), D3DXVECTOR3(1.5, 10, 0.5), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 0, 255));

Player* sqr1 = new Player(D3DXVECTOR3(0, 0, 20 - 1), D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 255, 255));
Player* sqr2 = new Player(D3DXVECTOR3(10, 10, 20 - 1), D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 240, 240));

quicky::quicky() {

}

quicky::~quicky() {

}

void quicky::initialize(HWND hWnd) {

	Game::initialize(hWnd);

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
	fclose(controlFile);

	o1->init(this);
	o2->init(this);
	o3->init(this);
	o4->init(this);
	sqr1->init(this);
	sqr2->init(this);

	sqr1->assignControl(controlDoc);
	sqr2->assignControl(controlDoc);
}

void quicky::update() {

	for (int i = 0; i < vEntities.size(); i++) {
		vEntities[i]->update(deltaTime);
	}

	sqr1->update(deltaTime, vEntities);
	sqr2->update(deltaTime, vEntities);

	// D3DXVECTOR3 out_;
	// bool onScreen = false;
	// onScreen = graphics->camera->pointOnScreen(out_, sqr1->pos, worldMat);
	// printf("%d, %.2f, %.2f\n", onScreen, out_.x, out_.y);

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

void quicky::updateKeyboard() {

}

void quicky::keyPress(int key) {

}

void quicky::keyRelease(int key) {

}