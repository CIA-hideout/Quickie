#include "Camera.h"
#include <stdio.h>


Camera::Camera() {
}

Camera::Camera(CameraType cT, float fov, D3DVIEWPORT9& viewPort) {

	cameraType = cT;
	pos = D3DXVECTOR3(0.0f, 0.0f, -10.0f);
	originalPos = pos;
	look = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	vp = viewPort;

	D3DXMatrixPerspectiveFovLH(&projection, fov, vp.Width / vp.Height, vp.MinZ, vp.MaxZ);

	cameraEffect.insert(std::pair<CameraState, float>(CS_SHAKE, 0.0f));

}


Camera::~Camera() {
}

void Camera::getViewMatrix(D3DXMATRIX* v_) {

	if (cameraEffect.at(CS_SHAKE) > 0.0f) {
		std::random_device rdev;
		std::mt19937 generator(rdev());
		std::uniform_real_distribution<float> distribution(-shakeIntensity, shakeIntensity);

		pos.x = originalPos.x + distribution(generator) / 15.0f;
		pos.y = originalPos.y + distribution(generator) / 15.0f;
		pos.z = originalPos.z + distribution(generator) / 15.0f;
		D3DXMatrixLookAtLH(v_, &pos, &look, &up);
	}
	else {
		D3DXMatrixLookAtLH(v_, &originalPos, &look, &up);
	}
	
}

void Camera::pitch(float angle) {

	D3DXMATRIX T;
	D3DXMatrixRotationAxis(&T, &right, angle);

	// rotate _up and _look around _right vector
	D3DXVec3TransformCoord(&up, &up, &T);
	D3DXVec3TransformCoord(&look, &look, &T);
}

void Camera::roll(float angle) {

	// only roll for aircraft type
	if (cameraType == CAMERA_TYPE_FREE)
	{
		D3DXMATRIX T;
		D3DXMatrixRotationAxis(&T, &look, angle);

		// rotate _up and _right around _look vector
		D3DXVec3TransformCoord(&right, &right, &T);
		D3DXVec3TransformCoord(&up, &up, &T);
	}

}

void Camera::yaw(float angle) {

	D3DXMATRIX T;

	if (cameraType == CAMERA_TYPE_LAND_OBJECT) {
		D3DXMatrixRotationY(&T, angle);
	}
	else if (cameraType == CAMERA_TYPE_FREE) {
		D3DXMatrixRotationAxis(&T, &up, angle);
	}
	D3DXVec3TransformCoord(&right, &right, &T);
	D3DXVec3TransformCoord(&look, &look, &T);

}

void Camera::walk(float u) {
	if (cameraType == CAMERA_TYPE_LAND_OBJECT) {
		originalPos += D3DXVECTOR3(look.x, 0.0f, look.z) * u;
	}
	else if (cameraType == CAMERA_TYPE_FREE) {
		originalPos += look * u;
	}
}

void Camera::strafe(float u) {
	if (cameraType == CAMERA_TYPE_LAND_OBJECT) {
		originalPos += D3DXVECTOR3(right.x, 0.0f, right.z) * u;
	}
	else if (cameraType == CAMERA_TYPE_FREE) {
		originalPos += right * u;
	}
}

void Camera::fly(float u) {
	if (cameraType == CAMERA_TYPE_FREE) {
		originalPos += up * u;
	}
}

void Camera::pointOnScreen(D3DXVECTOR3& pOut, D3DXVECTOR3& pos) {

	D3DXMATRIX v;
	float x_, y_, z_, w_;
	D3DXVECTOR4 v4 = D3DXVECTOR4(pos.x, pos.y, pos.z, 1);

	D3DXMatrixIdentity(&v);
	v(3, 2) = 1 / vp.MinZ;
	v(3, 3) = 0;

	x_ = v(0, 0) * v4.x + v(0, 1) * v4.y + v(0, 2) * v4.z + v(0, 3) * v4.w;
	y_ = v(1, 0) * v4.x + v(1, 1) * v4.y + v(1, 2) * v4.z + v(1, 3) * v4.w;
	z_ = v(2, 0) * v4.x + v(2, 1) * v4.y + v(2, 2) * v4.z + v(2, 3) * v4.w;
	w_ = v(3, 0) * v4.x + v(3, 1) * v4.y + v(3, 2) * v4.z + v(3, 3) * v4.w;

	v4.x = x_;
	v4.y = y_;
	v4.z = z_;
	v4.w = w_;

	v4.x /= v4.w;
	v4.y /= v4.w;

	pOut.x = vp.Width * v4.x / 2 / projection(0, 0) + (vp.Width / 2);
	pOut.y = vp.Height / 2 - vp.Height * v4.y / 2 / projection(1, 1);
	pOut.z = vp.MinZ;

}

void Camera::pointInWorld(D3DXVECTOR3& pOut, D3DXVECTOR2& point, float z) {

	// R2 -> R3 | z

	float x_, y_ = 0;

	// normalize to -1 and 1
	x_ = (2 * (point.x - 0) / (vp.Width - 0)) - 1;
	y_ = -(2 * (point.y - 0) / (vp.Height - 0) - 1);
	pOut.z = z;

	pOut.x = x_ / vp.MinZ * z;
	pOut.y = y_ / vp.MinZ * z;

}

void Camera::update(float deltaTime) {
	for (std::map<CameraState, float>::iterator i = cameraEffect.begin(); i != cameraEffect.end(); i++) {
		if (i->second > 0.0f)
			i->second -= deltaTime;
	}
}

void Camera::shake(float duration, float intensity) {
	cameraEffect.at(CS_SHAKE) = duration;
	shakeIntensity = intensity;
}