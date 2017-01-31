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
	char					keyState[256];
	IDirectInput8*			di;
	IDirectInputDevice8*	keyboard;

public:

	std::map<int, bool>		keys;

	Input(HWND hWnd);
	virtual ~Input();
	void update();

	char getKeyState(int key) { return keyState[key]; }
	
};

