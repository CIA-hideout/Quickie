#pragma once



#define PI	3.14159265

#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <string>
#include <vector>

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
const UINT GAME_WIDTH = 1000;               // width of game in pixels
const UINT GAME_HEIGHT = 1000;               // height of game in pixels

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
