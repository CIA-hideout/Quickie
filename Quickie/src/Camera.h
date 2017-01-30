#pragma once

#include <d3d9.h>
#include <d3dx9.h>

enum CameraType {
	CAMERA_TYPE_LAND_OBJECT,
	CAMERA_TYPE_FREE
};

class Camera {

public:

	Camera();
	Camera(CameraType ct, float, float);
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

	CameraType	cameraType;
	D3DXVECTOR3	right;
	D3DXVECTOR3	up;
	D3DXVECTOR3	look;
	D3DXVECTOR3	pos;
	float fov, width, height;

	D3DXMATRIX	projection;

};

