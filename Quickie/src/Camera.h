#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include <map>

#include <random>

enum CameraState {
	CS_SHAKE,
	CS_STATIONARY
};

class Camera {

public:

	Camera();
	Camera(float, D3DVIEWPORT9&);
	~Camera();

	void strafe(float);
	void fly(float);
	void walk(float);

	void pitch(float);
	void yaw(float);
	void roll(float);

	void getViewMatrix(D3DXMATRIX*);

	void update(float);

	D3DXVECTOR2 pointOnScreen(D3DXVECTOR2&, D3DXVECTOR3&);
	D3DXVECTOR3 pointInWorld(D3DXVECTOR3&, D3DXVECTOR2&, float);

	void shake(float, float);

	std::map<CameraState, float>	cameraEffect;

	D3DXVECTOR3						right;
	D3DXVECTOR3						up;
	D3DXVECTOR3						look;
	D3DXVECTOR3						pos, originalPos;
	float							fov, width, height, shakeIntensity;

	D3DVIEWPORT9					vp;

	D3DXMATRIX						projection;

};

