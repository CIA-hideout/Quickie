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
#define DIMENSION_NON_EXISTANT		D3DXVECTOR3(0, 0, 0)		// use if obstacles are not needed

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

// Default Font
const int FONT_HEIGHT			= 50;
const UINT FONT_WIDTH			= 25;
const UINT FONT_WEIGHT			= 500;
const bool FONT_ITALICS			= false;
const std::string FONT_NAME		= "Air Americana";

const UCHAR ESC_KEY				= VK_ESCAPE;       // escape key
const UCHAR ALT_KEY				= VK_MENU;         // Alt key
const UCHAR ENTER_KEY			= VK_RETURN;       // Enter key
const UCHAR LEFT_KEY			= DIK_LEFT;
const UCHAR RIGHT_KEY			= DIK_RIGHT;
const UCHAR UP_KEY				= DIK_UP;
const UCHAR DOWN_KEY			= DIK_DOWN;
const UCHAR SPACEBAR			= 0x20;

// for spawning objects on screen
const int SPAWN_LEFT[] = {-15, -5 };	// -15 < pos.x < -5
const int SPAWN_CENTER[] = {-5, 5};		// - 5 < pos.x <  5
const int SPAWN_RIGHT[] = {5, 15};		//   5 < pos.x < 15
