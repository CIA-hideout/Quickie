#include "CollisionManager.h"

#define C_CT_AABB_AABB(v1, v2)	(v1->collisionType == CT_AABB && v2->collisionType == CT_AABB)
#define C_CT_OOBB_OOBB(v1, v2)	(v1->collisionType == CT_OOBB && v2->collisionType == CT_OOBB)
#define C_CT_S_S(v1, v2)		(v1->collisionType == CT_S && v2->collisionType == CT_S)

#define P_DIST_3(p1, p2)		sqrt(pow((float)p1.x - p2.x, 2) + pow((float)p1.y - p2.y, 2) + pow((float)p1.z - p1.z, 2))
#define P_DIST_2(p1, p2)		sqrt(pow((float)p1.x - p2.x, 2) + pow((float)p1.y - p2.y, 2))

#define CROSS_2(v1, v2)			v1.x * v2.y - v1.y * v2.x


CollisionManager::CollisionManager() {

}

CollisionManager::~CollisionManager() {

}

bool CollisionManager::collideAABB(VertexShape* v1, VertexShape* v2) {

	computeAABB(v1);
	computeAABB(v2);

	bool collides = false;

	if (v1->max.x < v2->min.x || v1->min.x > v2->max.x || v1->max.y < v2->min.y || v1->min.y > v2->max.y || v1->max.z < v2->min.z || v1->min.z > v2->max.z)
		return collides;
	else
		return true;
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

	//t_ = (CROSS_2((c - a), r)) / CROSS_2(s, r);
	//u_ = (CROSS_2((a - c), s)) / CROSS_2(r, s);

	if (0 < t_ && t_ < 1 && 0 < u_ && u_ < 1) {
		pOut = c + u_ * s;
		return true;
	}

 	return false;
}

bool CollisionManager::rayObjectIntersect(D3DXVECTOR3& pOut, D3DXVECTOR4& pNorm, D3DXVECTOR3& pStart, D3DXVECTOR3& pEnd, VertexShape* vS) {

	int							closest = -1;
	float						dx, dy, tempVar, cDist = 999;
	D3DXVECTOR3					currPoint, rayStart, rayEnd, tStart, tEnd, intersection;
	D3DXVECTOR3					v;
	std::vector<D3DXVECTOR3>	posV;

	if (vS->collisionType == CT_AABB) {
		CollisionManager::computeAABB(vS);
	}

	rayStart = pStart;
	rayEnd = pEnd;

	// [0] top
	// min.x, max.y	->	max.x, max.y

	tStart.x = vS->min.x;
	tStart.y = vS->max.y;

	tEnd.x = vS->max.x;
	tEnd.y = vS->max.y;

	if (CollisionManager::lineSegmentIntersect(intersection, tStart, tEnd, rayStart, rayEnd)) {
		v.x = intersection.x;
		v.y = intersection.y;
		posV.push_back(v);
	}

	// [1] botom
	// min.x, min.y	->	max.x, min.y

	tStart.x = vS->min.x;
	tStart.y = vS->min.y;

	tEnd.x = vS->max.x;
	tEnd.y = vS->min.y;

	if (CollisionManager::lineSegmentIntersect(intersection, tStart, tEnd, rayStart, rayEnd)) {
		v.x = intersection.x;
		v.y = intersection.y;
		posV.push_back(v);
	}

	// [2] left
	// min.x, max.y	->	min.x, min.y

	tStart.x = vS->min.x;
	tStart.y = vS->max.y;

	tEnd.x = vS->min.x;
	tEnd.y = vS->min.y;

	if (CollisionManager::lineSegmentIntersect(intersection, tStart, tEnd, rayStart, rayEnd)) {
		v.x = intersection.x;
		v.y = intersection.y;
		posV.push_back(v);
	}

	// [3] right
	// max.x, max.y	->	max.x, min.y

	tStart.x = vS->max.x;
	tStart.y = vS->max.y;

	tEnd.x = vS->max.x;
	tEnd.y = vS->min.y;

	if (CollisionManager::lineSegmentIntersect(intersection, tStart, tEnd, rayStart, rayEnd)) {
		v.x = intersection.x;
		v.y = intersection.y;
		posV.push_back(v);
	}

	// the point of intersection will be the one closest to pStart
	// pNorm stores the normal vector

	for (int i = 0; i < posV.size(); i++) {
		tempVar = P_DIST_2(posV[i], pStart);
		if (tempVar < cDist) {
			cDist = tempVar;
			closest = i;
		}
	}

	if (closest == -1) {
		return false;
	}

	dx = rayStart.x - posV[closest].x;
	dy = rayStart.y - posV[closest].y;

	pNorm.x = -dy;
	pNorm.y = dx;
	pNorm.z = dy;
	pNorm.w = -dx;

	pOut = posV[closest];
	return true;

}

float CollisionManager::pDist2(const D3DXVECTOR3& p1, const D3DXVECTOR3& p2) {
	return sqrt(pow((float)p1.x - p2.x, 2) + pow((float)p1.y - p2.y, 2));
}

float CollisionManager::pDist3(const D3DXVECTOR3& p1, const D3DXVECTOR3& p2) {
	return sqrt(pow((float)p1.x - p2.x, 2) + pow((float)p1.y - p2.y, 2) + pow((float)p1.z - p1.z, 2));
}
