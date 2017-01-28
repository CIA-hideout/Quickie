#include "CollisionManager.h"

#define C_CT_AABB_AABB(v1, v2)	(v1->collisionType == CT_AABB && v2->collisionType == CT_AABB)
#define C_CT_OOBB_OOBB(v1, v2)	(v1->collisionType == CT_OOBB && v2->collisionType == CT_OOBB)
#define C_CT_S_S(v1, v2)			(v1->collisionType == CT_S && v2->collisionType == CT_S)

#define P_DIST(p1, p2) sqrt(pow((float)p1.x - p2.x, 2) + pow((float)p1.y - p2.y, 2) + pow((float)p1.z - p1.z, 2));

CollisionManager::CollisionManager() {

}

CollisionManager::~CollisionManager() {

}

void CollisionManager::addEntity(VertexShape* vs) {

}

void CollisionManager::removeEntity(VertexShape* vs) {

}

void CollisionManager::checkCollision(std::vector<VertexShape*>& vE) {

	D3DXVECTOR3 cV1, cV2;

	for (int i = 0; i < vE.size(); i++) {

		if (vE[i]->collisionType == CT_N)
			break;

		for (int j = 0; j < vE.size(); j++) {

			if (vE[j]->collisionType == CT_N)
				break;

			if (C_CT_AABB_AABB(vE[i], vE[j])) {
				if (collideAABB(vE[i], vE[j])) {

				}
			}

			else if (C_CT_OOBB_OOBB(vE[i], vE[j])) {
				if (collideOOBB(vE[i], vE[j], cV1)) {

				}
			}

			else if (C_CT_S_S(vE[i], vE[j])) {
				if (collideS(vE[i], vE[j], cV1)) {

				}
			}

			// probably some mixed type
			// 殺してください

		}
	}
}

bool CollisionManager::collideAABB(VertexShape* v1, VertexShape* v2) {

	computeAABB(v1, v1->min, v2->max);
	computeAABB(v2, v2->min, v2->max);

	bool collides = false;

	if (v1->max.x < v2->min.x || v1->min.x > v2->max.x || v1->max.y < v2->min.y || v1->min.y > v2->max.y || v1->max.z < v2->min.z || v1->min.z > v2->max.z) {
		printf("no collide\n");
		return collides;
	}

	// collision happened
	else {
		printf("collides");
		return true;
	}
}

bool CollisionManager::collideOOBB(VertexShape* v1, VertexShape* v2, D3DXVECTOR3& cV) {
	return false;
}

bool CollisionManager::collideS(VertexShape* v1, VertexShape* v2, D3DXVECTOR3& cV) {
	return false;
}

void CollisionManager::computeAABB(VertexShape* vs, D3DXVECTOR3& min, D3DXVECTOR3& max) {

	LVertex* v;
	D3DXMATRIX mat;

	vs->meshPtr->LockVertexBuffer(0, (void**)&v);

	max.x = -999; max.y = -999; max.z = -999;
	min.x = 999; min.y = 999; min.z = 999;

	for (int i = 0; i < vs->vertexCount; i++) {

		D3DXMatrixTranslation(&mat, vs->pos.x + v->x, vs->pos.y + v->y, vs->pos.z + v->z);

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

	vs->meshPtr->UnlockVertexBuffer();

	vs->max = max;
	vs->min = min;

}