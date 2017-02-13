#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include <map>

#include <random>

enum CameraState {
	CS_SHAKE,
	CS_STATIONARY
};

enum CameraType {
	CAMERA_TYPE_LAND_OBJECT,
	CAMERA_TYPE_FREE
};

namespace cameraNS
{
	const int x = 29;
	const int cols = x;
	const int y = 29;
	const int rows = y / 2;
	const int total = x + y;
}

class Camera {

public:

	Camera();
	Camera(CameraType ct, float fov, D3DVIEWPORT9& viewPort);
	~Camera();

	void strafe(float);
	void fly(float);
	void walk(float);

	void pitch(float);
	void yaw(float);
	void roll(float);

	void getViewMatrix(D3DXMATRIX*);
	void setCameraType(CameraType);
	void getPosition(D3DXVECTOR3&);
	void setPosition(D3DXVECTOR3&);
	void getRight(D3DXVECTOR3&);
	void getUp(D3DXVECTOR3&);
	void getLock(D3DXVECTOR3&);

	void update(float);

	D3DXVECTOR2 pointOnScreen(D3DXVECTOR2&, D3DXVECTOR3&);
	D3DXVECTOR3 pointInWorld(D3DXVECTOR3&, D3DXVECTOR2&, float);

	void shake(float, float);

	std::map<CameraState, float>	cameraEffect;

	CameraType						cameraType;
	D3DXVECTOR3						right;
	D3DXVECTOR3						up;
	D3DXVECTOR3						look;
	D3DXVECTOR3						pos, originalPos;
	float							fov, width, height, shakeIntensity;

	D3DVIEWPORT9					vp;

	D3DXMATRIX						projection;

};

