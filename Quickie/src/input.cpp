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
		keys.insert(std::pair<int, bool>(i, false));
		keysPressed.insert(std::pair<int, bool>(i, false));
	}
}


Input::~Input() {
	di->Release();
	keyboard->Release();
}

void Input::update() {
	keyboard->Poll();
	if (!SUCCEEDED(keyboard->GetDeviceState(inputNS::KEYS_ARR_LENGTH, (LPVOID)&keyState)))
		keyboard->Acquire();
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