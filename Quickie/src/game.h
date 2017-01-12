#pragma once

#include <windows.h>
#include <Mmsystem.h>
#include <vector>

#include "graphics.h"
#include "constants.h"
#include "gameError.h"
#include "input.h"
#include "textureManager.h"
#include "image.h"

class Game {
protected:
	// common game properties

	Graphics		*graphics;      
	Input			*input;          
	HWND			hwnd;            
	HRESULT			hr;              
	LARGE_INTEGER	timeStart; 
	LARGE_INTEGER	timeEnd;   
	LARGE_INTEGER	timerFreq; 
	float			deltaTime;       
	float			fps;             
	DWORD			sleepTime;       
	bool			paused;          
	bool			initialized;

public:

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
};
