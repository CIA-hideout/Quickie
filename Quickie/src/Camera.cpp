#include "Camera.h"


Camera::Camera() {
}

Camera::Camera(CameraType cT, float fov, float aR) {

	cameraType = cT;
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	look = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	D3DXMatrixPerspectiveFovLH(&projection, fov, aR, 1.0f, 1000.0f);

}


Camera::~Camera() {
}

void Camera::getViewMatrix(D3DXMATRIX* v_) {
	D3DXMatrixLookAtLH(v_, &pos, &look, &up);
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
		pos += D3DXVECTOR3(look.x, 0.0f, look.z) * u;
	}
	else if (cameraType == CAMERA_TYPE_FREE) {
		pos += look * u;
	}
}

void Camera::strafe(float u) {
	if (cameraType == CAMERA_TYPE_LAND_OBJECT) {
		pos += D3DXVECTOR3(right.x, 0.0f, right.z) * u;
	}
	else if (cameraType == CAMERA_TYPE_FREE) {
		pos += right * u;
	}
}

void Camera::fly(float u) {
	if (cameraType == CAMERA_TYPE_FREE) {
		pos += up * u;
	}
}
