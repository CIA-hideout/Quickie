#include "Input.h"

Input::Input(HWND hWnd) {

	this->hWnd = hWnd;

	DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&di, NULL);

	di->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	keyboard->SetDataFormat(&c_dfDIKeyboard);
	keyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	HRESULT hr = keyboard->Acquire();

	di->CreateDevice(GUID_SysMouse, &mouse, NULL);
	mouse->SetDataFormat(&c_dfDIMouse);
	mouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	HRESULT hr_ = mouse->Acquire();

	for (int i = DIK_ESCAPE; i <= DIK_MEDIASELECT; i++) {
		keys.insert(std::pair<int, bool>(i, false));
		keysPressed.insert(std::pair<int, bool>(i, false));
	}
}


Input::~Input() {
	di->Release();
	keyboard->Release();
	mouse->Release();
}

void Input::update() {
	keyboard->Poll();
	if (!SUCCEEDED(keyboard->GetDeviceState(inputNS::KEYS_ARR_LENGTH, (LPVOID)&keyState)))
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

//=============================================================================
// Return true if the specified VIRTUAL KEY has been pressed in the most recent
// frame. Key presses are erased at the end of each frame.
//=============================================================================
bool Input::wasKeyPressed(int i)
{
	if (i < inputNS::KEYS_ARR_LENGTH)
		return keysPressed[i];

	return false;
}

//=============================================================================
// Clear the specified key press
//=============================================================================
void Input::clearKeyPress(int i)
{
	if (i < inputNS::KEYS_ARR_LENGTH)
		keysPressed[i] = false;
}

void Input::clearAll()
{
	for (int i = 0; i < inputNS::KEYS_ARR_LENGTH; ++i)
	{
		keysPressed[i] = false;
	}
}