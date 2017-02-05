#pragma once

#define PI	3.14159265

#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <string>
#include <vector>

#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

// color RGB for D3DXVECTOR3
#define COLOR_RED D3DXVECTOR3(255, 0, 0)
#define COLOR_YELLOW D3DXVECTOR3(255, 255, 0)
#define COLOR_PURPLE D3DXVECTOR3(255, 0, 255)
#define COLOR_GREEN D3DXVECTOR3(0, 255, 0)
#define COLOR_BLUE D3DXVECTOR3(0, 0, 255)
#define COLOR_WHITE D3DXVECTOR3(255, 255, 255)

// define dimensions of obstacles
#define DIMENSION_HORIZONTAL_SMALL	D3DXVECTOR3( 6, 1.5, 0.5)
#define DIMENSION_HORIZONTAL_MEDIUM D3DXVECTOR3(12, 1.5, 0.5)
#define DIMENSION_HORIZONTAL_LARGE	D3DXVECTOR3(25, 1.5, 0.5)
#define DIMENSION_VERTICAL_SMALL	D3DXVECTOR3(1.5,  6, 0.5)
#define DIMENSION_VERTICAL_MEDIUM	D3DXVECTOR3(1.5, 12, 0.5)
#define DIMENSION_VERTICAL_LARGE	D3DXVECTOR3(1.5, 25, 0.5)
#define DIMENSION_NON_EXISTANT		D3DXVECTOR3(0, 0, 0)			// use if obstacles are not needed
#define DIMENSION_ALMOST_ZERO		D3DXVECTOR3(0.01, 0.01, 0.01)	// use for scaling as 0 * n = 0

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(0,0,0,0)  // transparent color (magenta)

//-----------------------------------------------
//                  Constants
//-----------------------------------------------

// window
const char CLASS_NAME[] = "quicky";
const char GAME_TITLE[] = "Quickie";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH = 1280;               // width of game in pixels
const UINT GAME_HEIGHT = 720;               // height of game in pixels
const float ASPECT_RATIO = (float)GAME_WIDTH / GAME_HEIGHT;

// game
const float FRAME_RATE = 200.0f;                // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f / FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f / MIN_FRAME_RATE; // maximum time used in calculations
const float FOV = PI * 0.5;

// for spawning objects on screen
const int SPAWN_LEFT[] = {-15, -5 };	// -15 < pos.x < -5
const int SPAWN_CENTER[] = {-5, 5};		// - 5 < pos.x <  5
const int SPAWN_RIGHT[] = {5, 15};		//   5 < pos.x < 15

// game time between each level
const float LEVEL_TIME = 10.0f;

// audio file required by audio.cpp
// WAVE_BANK must be the location of the xwb file
const char WAVE_BANK[] = "resource\\audio\\Win\\WaveBank.xwb";
// SOUND_BANK must be location of .xsb file
const char SOUND_BANK[] = "resource\\audio\\Win\\SoundBank.xsb";
// XGS_FILE must be location of .xgs file.
const char XGS_FILE[] = "resource\\audio\\Win\\quickie.xgs";

// Sound cues
const char BGM1[] = "bgm1";
const char BGM2[] = "bgm2";
const char BGM3[] = "bgm3";
const char BGM4[] = "bgm4";
const char BGM5[] = "bgm5";
