#pragma once

#include <dinput.h>
#include <Windows.h>
#include <Windowsx.h>
#include <stdio.h>
#include <map>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class Input {

private:

	HWND					hWnd;
	DIMOUSESTATE			mouseState;
	POINT					position;
	char					keyState[256];
	IDirectInput8*			di;
	IDirectInputDevice8*	keyboard;
	IDirectInputDevice8*	mouse;

public:

	std::map<int, bool>		keys;

	Input(HWND hWnd);
	virtual ~Input();
	void update();
	bool getMouseButton(char button);

	char getKeyState(int key) { return keyState[key]; }
	long GetPosX() { return position.x; }
	long GetPosY() { return position.y; }
	long GetDeltaX() { return mouseState.lX; }
	long GetDeltaY() { return mouseState.lY; }
	long GetDeltaWheel() { return mouseState.lZ; }
	
};

