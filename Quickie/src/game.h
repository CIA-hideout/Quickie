#pragma once

#include <windows.h>
#include <Mmsystem.h>
#include <DxErr.h>
#include <vector>

#include "constants.h"
#include "graphics.h"
#include "gameError.h"
#include "input.h"

#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/document.h"
#include "State.h"
#include <stack>

#include <random>

#pragma comment(lib, "dxerr.lib")

#define MINMAXRAND(min_, max_) rand() % (max_ - min_ + 1) + (float)min_

class Game {
public:

	Graphics					*graphics;
	Input						*input;
	HWND						hwnd;
	HRESULT						hr;
	LARGE_INTEGER				timeStart;
	LARGE_INTEGER				timeEnd;
	LARGE_INTEGER				timerFreq;
	float						deltaTime;
	float						fps;
	DWORD						sleepTime;
	bool						paused;
	bool						initialized;
	float						fov;
	std::stack<State*>			gameState;

	D3DXMATRIX		worldMat;

	LPD3DXBUFFER*	ppAdjacency;

	Game();
	virtual ~Game();

	LRESULT messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	virtual void initialize(HWND hwnd);

	virtual void run(HWND);

	virtual void releaseAll();

	virtual void resetAll();

	virtual void deleteAll();

	virtual void renderGame();

	virtual void handleLostGraphicsDevice();

	Graphics* getGraphics() { return graphics; }

	Input* getInput() { return input; }

	void exitGame() { PostMessage(hwnd, WM_DESTROY, 0, 0); }

	virtual void update() = 0;

	virtual void ai() = 0;

	virtual void collisions() = 0;

	virtual void render() = 0;

	virtual void updateKeyboard() = 0;

	virtual void keyPress(int key) = 0;

	virtual void keyRelease(int key) = 0;
};
