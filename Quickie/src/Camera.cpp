#include "Camera.h"
#include <stdio.h>


Camera::Camera() {
}

Camera::Camera(float fov, D3DVIEWPORT9& viewPort) {

	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	look = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	originalPos = pos;
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
		std::uniform_real_distribution<float> distribution(-shakeIntensity / 15.0f, shakeIntensity / 15.0f);

		pos.x = originalPos.x + distribution(generator);
		pos.y = originalPos.y + distribution(generator);
		pos.z = originalPos.z + distribution(generator);
		D3DXMatrixLookAtLH(v_, &pos, &look, &up);
	}
	else {
		D3DXMatrixLookAtLH(v_, &originalPos, &look, &up);
	}

}

void Camera::pitch(float angle) {

	D3DXMATRIX T;
	D3DXMatrixRotationAxis(&T, &right, angle);

	D3DXVec3TransformCoord(&up, &up, &T);
	D3DXVec3TransformCoord(&look, &look, &T);
}

void Camera::roll(float angle) {
	D3DXMATRIX T;
	D3DXMatrixRotationAxis(&T, &look, angle);

	D3DXVec3TransformCoord(&right, &right, &T);
	D3DXVec3TransformCoord(&up, &up, &T);
}

void Camera::yaw(float angle) {

	D3DXMATRIX T;

	D3DXMatrixRotationAxis(&T, &up, angle);
	D3DXVec3TransformCoord(&right, &right, &T);
	D3DXVec3TransformCoord(&look, &look, &T);

}

void Camera::walk(float u) {
	originalPos += look * u;
}

void Camera::strafe(float u) {
	originalPos += right * u;
}

void Camera::fly(float u) {
	originalPos += up * u;
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

D3DXVECTOR2 Camera::pointOnScreen(D3DXVECTOR2& pOut, D3DXVECTOR3& pos) {

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

	// normalized screen coord
	v4.x /= v4.w;
	v4.y /= v4.w;

	pOut.x = vp.Width * v4.x / 2 + vp.Width / 2;
	pOut.y = vp.Height / 2 - vp.Height * v4.y / 2;

	D3DXVECTOR2 retVal;

	retVal.x = pOut.x;
	retVal.y = pOut.y;

	return retVal;

}

D3DXVECTOR3 Camera::pointInWorld(D3DXVECTOR3& pOut, D3DXVECTOR2& point, float z) {

	// R2 -> R3 | z

	float x_, y_ = 0;
	float min_ = -1;
	float max_ = 1;

	// normalize to -1 and 1
	x_ = ((max_ - min_) * (point.x) / (vp.Width)) + min_;
	y_ = -((max_ - min_) * (point.y) / (vp.Height) + min_);

	pOut.x = x_ / vp.MinZ * z;
	pOut.y = y_ / vp.MinZ * z;
	pOut.z = z;

	D3DXVECTOR3 retVal;

	retVal.x = pOut.x;
	retVal.y = pOut.y;
	retVal.z = pOut.z;

	return retVal;

}