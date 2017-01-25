#pragma once

#define PI	3.14159265

#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <string>
#include <vector>

#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

// color RGB for D3DXVECTOR3
#define COLOR_RED D3DXVECTOR3(255, 0, 0)
#define COLOR_YELLOW D3DXVECTOR3(255, 255, 0)
#define COLOR_PURPLE D3DXVECTOR3(255, 0, 255)
#define COLOR_GREEN D3DXVECTOR3(0, 255, 0)
#define COLOR_BLUE D3DXVECTOR3(0, 0, 255)
#define COLOR_WHITE D3DXVECTOR3(255, 255, 255)

// define size of obstacles
#define DIMENSION_SMALL D3DXVECTOR3(7, 1, 2.5)
#define DIMENSION_MEDIUM D3DXVECTOR3(10, 1, 2.5)


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
const char CLASS_NAME[] = "Pixl";
const char GAME_TITLE[] = "Pixl";
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

const UCHAR ESC_KEY = VK_ESCAPE;       // escape key
const UCHAR ALT_KEY = VK_MENU;         // Alt key
const UCHAR ENTER_KEY = VK_RETURN;       // Enter key
const UCHAR SHIP_ROTATE_LEFT = VK_LEFT;
const UCHAR SHIP_ROTATE_RIGHT = VK_RIGHT;
const UCHAR SHIP_ADD_V = VK_UP;
const UCHAR SHIP_SUBTRACT_V = VK_DOWN;
const UCHAR SPACEBAR = 0x20;

// for spawning objects on screen
const int SPAWN_LEFT[] = {-15, -5 };	// -15 < pos.x < -5
const int SPAWN_CENTER[] = {-5, 5};		// - 5 < pos.x <  5 
const int SPAWN_RIGHT[] = {5, 15};		//   5 < pos.x < 15
