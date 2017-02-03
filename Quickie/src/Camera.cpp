#include "Camera.h"
#include <stdio.h>


Camera::Camera() {
}

Camera::Camera(CameraType cT, float fov, D3DVIEWPORT9& viewPort) {

	cameraType = cT;
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	look = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	vp = viewPort;

	D3DXMatrixPerspectiveFovLH(&projection, fov, vp.Width / vp.Height, vp.MinZ, vp.MaxZ);

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

void Camera::pointOnScreen(D3DXVECTOR3& pOut, D3DXVECTOR3& pos, D3DXMATRIX& w) {

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
	pOut.z = 0;

	printf("%.2f, %.2f, ", pOut.x, pOut.y);

}

void Camera::pointInWorld(D3DXVECTOR3& pOut, D3DXVECTOR2& point, float z) {

	// R2 -> R3 | z

	float x_, y_, z_, w_;
	D3DXMATRIX temp,invM;
	getViewMatrix(&temp);
	temp = projection * temp;

	D3DXVECTOR4 v1, v2;

	// normalize to -1 and 1
	pOut.x = v1.x = (2 * (point.x - 0) / (vp.Width - 0)) - 1;
	pOut.y = v1.y = (2 * (point.y - 0) / (vp.Height - 0)) - 1;
	pOut.z = v1.z = z;
	v1.w = 1;

	D3DXMatrixInverse(&invM, 0, &temp);

	v2.x = v1.x * invM(0, 0) + v1.y * invM(0, 1) + v1.z * invM(0, 2) + v1.w * invM(0, 3);
	v2.y = v1.x * invM(1, 0) + v1.y * invM(1, 1) + v1.z * invM(1, 2) + v1.w * invM(1, 3);
	v2.z = v1.x * invM(2, 0) + v1.y * invM(2, 1) + v1.z * invM(2, 2) + v1.w * invM(2, 3);
	v2.w = v1.x * invM(3, 0) + v1.y * invM(3, 1) + v1.z * invM(3, 2) + v1.w * invM(3, 3);

	v2.x *= v2.w;
	v2.y *= v2.w;
	v2.z *= v2.w;

	pOut.x = -v2.x;
	pOut.y = -v2.y;
	pOut.z = -v2.z;

}