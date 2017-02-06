#include "VertexShape.h"


VertexShape::VertexShape() {
	static int id_ = 0;
	this->id = id_++;
	meshPtr = nullptr;
}

VertexShape::~VertexShape() {
}

void VertexShape::init(Graphics* g, Input* i) {

}

void VertexShape::draw(D3DXMATRIX& worldMat) {
}

void VertexShape::update(float deltaTime) {

}

bool VertexShape::collidesWith(VertexShape& vShape) {

	computeBoundingBox();
	vShape.computeBoundingBox();

	if (max.x < vShape.min.x || min.x > vShape.max.x || max.y < vShape.min.y || min.y > vShape.max.y || max.z < vShape.min.z || min.z > vShape.max.z) {
		return false;
	}
	return true;

}

void VertexShape::computeBoundingBox() {

	LVertex* v;
	D3DXMATRIX mat;

	meshPtr->LockVertexBuffer(0, (void**)&v);

	max.x = -999; max.y = -999; max.z = -999;
	min.x = 999; min.y = 999; min.z = 999;

	for (int i = 0; i < vertexCount; i++) {

		D3DXMatrixTranslation(&mat, pos.x + v->x, pos.y + v->y, pos.z + v->z);

		if (max.x < mat(3, 0))
			max.x = mat(3, 0);
		if (max.y < mat(3, 1))
			max.y = mat(3, 1);
		if (max.z < mat(3, 2))
			max.z = mat(3, 2);

		if (min.x > mat(3, 0))
			min.x = mat(3, 0);
		if (max.y > mat(3, 1))
			min.y = mat(3, 1);
		if (min.z > mat(3, 2))
			min.z = mat(3, 2);

		v++;
	}

	meshPtr->UnlockVertexBuffer();

}

void VertexShape::computeBoundingSphere() {

	if (collisionType != CT_S)
		return;

	BYTE* v = 0;
	meshPtr->LockVertexBuffer(0, (void**)&v);

	D3DXComputeBoundingSphere(
		(D3DXVECTOR3*)v,
		meshPtr->GetNumVertices(),
		D3DXGetFVFVertexSize(meshPtr->GetFVF()),
		center,
		&radius
		);

	meshPtr->UnlockVertexBuffer();

}
