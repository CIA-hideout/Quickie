#pragma once

#include <dinput.h>
#include <Windows.h>
#include <Windowsx.h>
#include <stdio.h>
#include <map>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

namespace inputNS
{
	const int				KEYS_ARR_LENGTH = 256;
}

class Input {

private:

	HWND					hWnd;
	DIMOUSESTATE			mouseState;
	POINT					position;
	char					keyState[inputNS::KEYS_ARR_LENGTH];
	IDirectInput8*			di;
	IDirectInputDevice8*	keyboard;
	IDirectInputDevice8*	mouse;

public:

	std::map<int, bool>		keys;
	std::map<int, bool>		keysPressed;

	Input(HWND hWnd);
	virtual ~Input();
	void update();
	bool getMouseButton(char button);

	bool wasKeyPressed(int key);
	void clearKeyPress(int key);
	void clearAll();
	char getKeyState(int key) { return keyState[key]; }
	long GetPosX() { return position.x; }
	long GetPosY() { return position.y; }
	long GetDeltaX() { return mouseState.lX; }
	long GetDeltaY() { return mouseState.lY; }
	long GetDeltaWheel() { return mouseState.lZ; }
	
};

