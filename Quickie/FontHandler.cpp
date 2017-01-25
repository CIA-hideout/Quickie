#include "src/FontHandler.h"
#include <dinput.h>

FontHandler::FontHandler() 
{
	graphics = nullptr;
	font = nullptr;
	font_rect = new RECT();

	height = 0;
	width = 0;
	weight = 0;
	italics = false;
	fontName = "Arial";
}

FontHandler::~FontHandler()
{
}


bool FontHandler::initialize(Graphics* g)
{
	try{
		graphics = g;                               // the graphics object
	}
	catch (...) { return false; }
	return true;
}

bool FontHandler::createFont()
{
	try
	{
		D3DXCreateFont(graphics->get3Ddevice(),			//D3D Device

			height,										//Font height

			width,										//Font width

			weight,										//Font Weight

			1,											//MipLevels

			italics,									//Italic
			
			DEFAULT_CHARSET,							//CharSet

			OUT_DEFAULT_PRECIS,							//OutputPrecision

			ANTIALIASED_QUALITY,						//Quality

			DEFAULT_PITCH | FF_DONTCARE,				//PitchAndFamily

			fontName.c_str(),							//pointer to Facename

			&font);										//ppFont
	}
	catch (...)
	{
		return false;
	}

	return true;
}

bool FontHandler::createFont(int h, UINT wid, UINT wei, bool i, std::string fN)
{
	height = h;
	width = wid;
	weight = wei;
	italics = i;
	fontName = fN;

	try
	{
		D3DXCreateFont(graphics->get3Ddevice(),     //D3D Device

			h,										//Font height

			wid,									//Font width

			wei,									//Font Weight

			1,										//MipLevels

			i,										//Italic

			DEFAULT_CHARSET,						//CharSet

			OUT_DEFAULT_PRECIS,						//OutputPrecision

			ANTIALIASED_QUALITY,					//Quality

			DEFAULT_PITCH | FF_DONTCARE,			//PitchAndFamily

			fN.c_str(),								//pFacename

			&font);									//ppFont
	}
	catch (...)
	{
		return false;
	}
	
	return true;
}

void FontHandler::print(int x, int y, std::string s)
{
	SetRect(font_rect, x, y, x, y);			// left, top, right, bottom

	font->DrawText(nullptr,			//pointer to Sprite

		s.c_str(),					//pointer to String

		-1,							//Count

		font_rect,					//pointer to Rect

		DT_LEFT | DT_NOCLIP,		//Format

		0xffffffff);				//Color
}


