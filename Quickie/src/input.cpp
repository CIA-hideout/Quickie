#include "Input.h"

Input::Input(HWND hWnd) {

	this->hWnd = hWnd;

	DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&di, NULL);

	di->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	keyboard->SetDataFormat(&c_dfDIKeyboard);
	keyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	keyboard->Acquire();

	di->CreateDevice(GUID_SysMouse, &mouse, NULL);
	mouse->SetDataFormat(&c_dfDIMouse);
	mouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	mouse->Acquire();

}


Input::~Input() {
	di->Release();
	keyboard->Release();
	mouse->Release();
}

void Input::update() {
	keyboard->Poll();
	if (!SUCCEEDED(keyboard->GetDeviceState(256, (LPVOID)&keyState)))
		keyboard->Acquire();
	mouse->Poll();
	if (!SUCCEEDED(mouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseState)))
		mouse->Acquire();

	GetCursorPos(&position);
	ScreenToClient(hWnd, &position);
}

bool Input::getMouseButton(char button) {
	return mouseState.rgbButtons[button] & 0x80;
}
