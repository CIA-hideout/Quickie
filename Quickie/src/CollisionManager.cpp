#include "CollisionManager.h"

#define C_CT_AABB_AABB(v1, v2)	(v1->collisionType == CT_AABB && v2->collisionType == CT_AABB)
#define C_CT_OOBB_OOBB(v1, v2)	(v1->collisionType == CT_OOBB && v2->collisionType == CT_OOBB)
#define C_CT_S_S(v1, v2)		(v1->collisionType == CT_S && v2->collisionType == CT_S)

#define P_DIST_3(p1, p2)		sqrt(pow((float)p1.x - p2.x, 2) + pow((float)p1.y - p2.y, 2) + pow((float)p1.z - p1.z, 2));
#define P_DIST_2(p1, p2)		sqrt(pow((float)p1.x - p2.x, 2) + pow((float)p1.y - p2.y, 2));

CollisionManager::CollisionManager() {

}

CollisionManager::~CollisionManager() {

}

bool CollisionManager::collideAABB(VertexShape* v1, VertexShape* v2) {

	computeAABB(v1);
	computeAABB(v2);

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

void CollisionManager::computeAABB(VertexShape* vs) {

	LVertex* v;
	D3DXMATRIX mat;

	vs->meshPtr->LockVertexBuffer(0, (void**)&v);

	vs->max.x = -999; vs->max.y = -999; vs->max.z = -999;
	vs->min.x = +999; vs->min.y = +999; vs->min.z = +999;

	for (int i = 0; i < vs->vertexCount; i++) {

		D3DXMatrixTranslation(&mat, vs->pos.x + v->x, vs->pos.y + v->y, vs->pos.z + v->z);

		if (vs->max.x < mat(3, 0))
			vs->max.x = mat(3, 0);
		if (vs->max.y < mat(3, 1))
			vs->max.y = mat(3, 1);
		if (vs->max.z < mat(3, 2))
			vs->max.z = mat(3, 2);

		if (vs->min.x > mat(3, 0))
			vs->min.x = mat(3, 0);
		if (vs->max.y > mat(3, 1))
			vs->min.y = mat(3, 1);
		if (vs->min.z > mat(3, 2))
			vs->min.z = mat(3, 2);

		v++;
	}

	vs->meshPtr->UnlockVertexBuffer();

}

bool CollisionManager::lineSegmentIntersect(D3DXVECTOR3& pOut, D3DXVECTOR3& pStart, D3DXVECTOR3& pEnd, D3DXVECTOR3& qStart, D3DXVECTOR3& qEnd) {

	// function to calculate line segment intersection,
	// pOut: reference to a D3DXVECTOR3. For point of intersection

	float t_, u_;

	D3DXVECTOR3 a, b, c, d, r, s;
	a = pStart;
	b = pEnd;
	c = qStart;
	d = qEnd;

	r = b - a;
	s = d - c;

	t_ = ((c.x * s.y - c.y * s.x) - (a.x * s.y - a.y * s.x)) / (r.x * s.y - r.y * s.x);
	u_ = ((a.x * r.y - a.y * r.x) - (c.x * r.y - c.y * r.x)) / (s.x * r.y - s.y * r.x);

	if (0 < t_ < 1 && 0 < u_ < 1) {

		// point of intersection
		pOut = b + t_ * r;
		return true;

	}

	return false;
}