#include "Camera.h"


Camera::Camera() {
}

Camera::Camera(CameraType cameraType_) {
	cameraType = cameraType_;
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	look = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
}


Camera::~Camera() {
}

void Camera::getViewMatrix(D3DXMATRIX* v_) {
	D3DXMatrixLookAtLH(v_, &pos, &look, &up);
}

void Camera::pitch(float angle_) {

	D3DXMATRIX T;
	D3DXMatrixRotationAxis(&T, &right, angle_);

	// rotate _up and _look around _right vector
	D3DXVec3TransformCoord(&up, &up, &T);
	D3DXVec3TransformCoord(&look, &look, &T);
}

void Camera::roll(float angle_) {

	// only roll for aircraft type
	if (cameraType == CAMERA_TYPE_FREE)
	{
		D3DXMATRIX T;
		D3DXMatrixRotationAxis(&T, &look, angle_);

		// rotate _up and _right around _look vector
		D3DXVec3TransformCoord(&right, &right, &T);
		D3DXVec3TransformCoord(&up, &up, &T);
	}

}

void Camera::yaw(float angle_) {

	D3DXMATRIX T;

	if (cameraType == CAMERA_TYPE_LAND_OBJECT) {
		D3DXMatrixRotationY(&T, angle_);
	}
	else if (cameraType == CAMERA_TYPE_FREE) {
		D3DXMatrixRotationAxis(&T, &up, angle_);
	}
	D3DXVec3TransformCoord(&right, &right, &T);
	D3DXVec3TransformCoord(&look, &look, &T);

}

void Camera::walk(float units_) {
	if (cameraType == CAMERA_TYPE_LAND_OBJECT) {
		pos += D3DXVECTOR3(look.x, 0.0f, look.z) * units_;
	}
	else if (cameraType == CAMERA_TYPE_FREE) {
		pos += look * units_;
	}
}

void Camera::strafe(float units_) {
	if (cameraType == CAMERA_TYPE_LAND_OBJECT) {
		pos += D3DXVECTOR3(right.x, 0.0f, right.z) * units_;
	}
	else if (cameraType == CAMERA_TYPE_FREE) {
		pos += right * units_;
	}
}

void Camera::fly(float units_) {
	if (cameraType == CAMERA_TYPE_FREE) {
		pos += up * units_;
	}
}