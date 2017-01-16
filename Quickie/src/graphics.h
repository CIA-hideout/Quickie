// please don't spam comments
// -LL

#pragma once 


#ifdef _DEBUG
#define D3D_DEBUG_INFO
#endif
#include <d3d9.h>
#include <d3dx9.h>
#include "constants.h"
#include "gameError.h"
#include "Camera.h"
#include <stdlib.h>
#include <stdio.h>
#include <timeapi.h>
#include <sstream>
#include <iomanip>
#include <fstream>

#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE	)

#define LP_TEXTURE  LPDIRECT3DTEXTURE9
#define LP_3DDEVICE LPDIRECT3DDEVICE9
#define LP_SPRITE   LPD3DXSPRITE
#define LP_3D       LPDIRECT3D9
#define VECTOR2     D3DXVECTOR2

#define COLOR_ARGB DWORD
#define SETCOLOR_ARGB(a,r,g,b) \
    ((COLOR_ARGB)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))

namespace graphicsNS {
    const COLOR_ARGB ORANGE  = D3DCOLOR_ARGB(255,255,165,  0);
    const COLOR_ARGB BROWN   = D3DCOLOR_ARGB(255,139, 69, 19);
    const COLOR_ARGB LTGRAY  = D3DCOLOR_ARGB(255,192,192,192);
    const COLOR_ARGB GRAY    = D3DCOLOR_ARGB(255,128,128,128);
    const COLOR_ARGB OLIVE   = D3DCOLOR_ARGB(255,128,128,  0);
    const COLOR_ARGB PURPLE  = D3DCOLOR_ARGB(255,128,  0,128);
    const COLOR_ARGB MAROON  = D3DCOLOR_ARGB(255,128,  0,  0);
    const COLOR_ARGB TEAL    = D3DCOLOR_ARGB(255,  0,128,128);
    const COLOR_ARGB GREEN   = D3DCOLOR_ARGB(255,  0,128,  0);
    const COLOR_ARGB NAVY    = D3DCOLOR_ARGB(255,  0,  0,128);
    const COLOR_ARGB WHITE   = D3DCOLOR_ARGB(255,255,255,255);
    const COLOR_ARGB YELLOW  = D3DCOLOR_ARGB(255,255,255,  0);
    const COLOR_ARGB MAGENTA = D3DCOLOR_ARGB(255,255,  0,255);
    const COLOR_ARGB RED     = D3DCOLOR_ARGB(255,255,  0,  0);
    const COLOR_ARGB CYAN    = D3DCOLOR_ARGB(255,  0,255,255);
    const COLOR_ARGB LIME    = D3DCOLOR_ARGB(255,  0,255,  0);
    const COLOR_ARGB BLUE    = D3DCOLOR_ARGB(255,  0,  0,255);
    const COLOR_ARGB BLACK   = D3DCOLOR_ARGB(255,  0,  0,  0);
    const COLOR_ARGB FILTER  = D3DCOLOR_ARGB(  0,  0,  0,  0);
    const COLOR_ARGB ALPHA25 = D3DCOLOR_ARGB( 64,255,255,255);
    const COLOR_ARGB ALPHA50 = D3DCOLOR_ARGB(128,255,255,255);
    const COLOR_ARGB BACK_COLOR =	BLACK;                    

    enum DISPLAY_MODE{
		TOGGLE,
		FULLSCREEN,
		WINDOW
	};
}

struct LVertex {
	float					x, y, z;
	DWORD					color;
};

struct BoundingBox {

	BoundingBox() {

		min.x = FLT_MAX;
		min.y = FLT_MAX;
		min.z = FLT_MAX;

		max.x = -FLT_MAX;
		max.y = -FLT_MAX;
		max.z = -FLT_MAX;

	}

	bool isPointInside(D3DXVECTOR3& v_) {

		if (v_.x >= min.x && v_.y >= min.y && v_.z >= min.z && v_.x <= max.x && v_.y <= max.y && v_.z <= max.z)
			return true;
		return false;

	}

	D3DXVECTOR3	min;
	D3DXVECTOR3	max;

};

struct SpriteData {
    int						width;			
    int						height;			
    float					x;				
    float					y;
    float					scale;			
    float					angle;			
    RECT					rect;			
    LP_TEXTURE				texture;		
    bool					flipHorizontal; 
    bool					flipVertical;   
};

class Graphics
{
private:

    LP_3D					direct3d;
    LP_3DDEVICE				device3d;
    LP_SPRITE				sprite;
    D3DPRESENT_PARAMETERS	d3dpp;
    D3DDISPLAYMODE			pMode;

    HRESULT					result;
    HWND					hwnd;
    bool					fullscreen;
    int						width;
    int						height;
    COLOR_ARGB				backColor;

public:

	Camera*					camera;

public:

	D3DVIEWPORT9			viewPort;

    void initD3Dpp();

	LPDIRECT3DVERTEXBUFFER9	pVertexBuffer;

    Graphics();

    virtual ~Graphics();

    void releaseAll();

    void initialize(HWND hw, int width, int height, bool fullscreen);

    HRESULT loadTexture(const char * filename, COLOR_ARGB transcolor, UINT &width, UINT &height, LP_TEXTURE &texture);

    HRESULT showBackbuffer();

    bool isAdapterCompatible();

    void drawSprite(const SpriteData &spriteData, COLOR_ARGB color = graphicsNS::WHITE);

    HRESULT reset();

    void changeDisplayMode(graphicsNS::DISPLAY_MODE mode = graphicsNS::TOGGLE);

    static float Vector2Length(const VECTOR2 *v) {return D3DXVec2Length(v);}

    static float Vector2Dot(const VECTOR2 *v1, const VECTOR2 *v2) {return D3DXVec2Dot(v1, v2);}

    static void Vector2Normalize(VECTOR2 *v) {D3DXVec2Normalize(v, v);}

    static VECTOR2* Vector2Transform(VECTOR2 *v, D3DXMATRIX *m) {return D3DXVec2TransformCoord(v,v,m);}

    LP_3D get3D() { return direct3d; }

    LP_3DDEVICE get3Ddevice() { return device3d; }

    LP_SPRITE getSprite() { return sprite; }

    HDC getDC() { return GetDC(hwnd); }

    HRESULT getDeviceState();

    bool getFullscreen() { return fullscreen; }
 
    void setBackColor(COLOR_ARGB c) {backColor = c;}

	bool CreateVertexBuffer(UINT, DWORD, DWORD, D3DPOOL, IDirect3DVertexBuffer9**, HANDLE);

    HRESULT beginScene() 
    {
        result = E_FAIL;
        if(device3d == NULL)
            return result;
        device3d->Clear(0, NULL, D3DCLEAR_TARGET, backColor, 1.0F, 0);
        result = device3d->BeginScene();
        return result;
    }

    HRESULT endScene() {
        result = E_FAIL;
        if(device3d)
            result = device3d->EndScene();
        return result;
    }

    void spriteBegin() {
        sprite->Begin(D3DXSPRITE_ALPHABLEND);
    }

    void spriteEnd() {
        sprite->End();
    }
};
