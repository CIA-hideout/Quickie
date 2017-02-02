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

public:

	std::map<int, bool>		keys;
	std::map<int, bool>		keysPressed;

	Input(HWND hWnd);
	virtual ~Input();
	void update();

	bool wasKeyPressed(int key);
	void clearKeyPress(int key);
	void clearAll();
	char getKeyState(int key) { return keyState[key]; }

};
