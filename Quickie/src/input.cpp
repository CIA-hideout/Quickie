#include "Input.h"

Input::Input(HWND hWnd) {

	this->hWnd = hWnd;

	DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&di, NULL);

	di->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	keyboard->SetDataFormat(&c_dfDIKeyboard);
	keyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	HRESULT hr = keyboard->Acquire();

	for (int i = 0; i < 256; i++) {
		keyState[i] = false;
	}

}


Input::~Input() {
	di->Release();
	keyboard->Release();
}

void Input::update() {
	keyboard->Poll();
	if (!SUCCEEDED(keyboard->GetDeviceState(256, (LPVOID)&keyState)))
		keyboard->Acquire();
}