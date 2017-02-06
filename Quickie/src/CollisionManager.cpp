#include "CollisionManager.h"

#define P_DIST_3(p1, p2)		sqrt(pow((float)p1.x - p2.x, 2) + pow((float)p1.y - p2.y, 2) + pow((float)p1.z - p1.z, 2))
#define P_DIST_2(p1, p2)		sqrt(pow((float)p1.x - p2.x, 2) + pow((float)p1.y - p2.y, 2))

#define CM						CollisionManager

CollisionManager::CollisionManager() {

}

CollisionManager::~CollisionManager() {

}

bool CollisionManager::collideAABB(VertexShape* v1, VertexShape* v2) {

	computeAABB(v1);
	computeAABB(v2);

	if (v1->max.x < v2->min.x || v1->min.x > v2->max.x || v1->max.y < v2->min.y || v1->min.y > v2->max.y)
		return false;
	else
		return true;
}

bool CollisionManager::collideOOBB(VertexShape* v1, VertexShape* v2, D3DXVECTOR3& cV) {
	return false;
}

bool CollisionManager::collidePixelPerfect(D3DXVECTOR3& pOut, VertexShape* v1, VertexShape* v2) {

	if (!collideAABB(v1, v2))
		return false;

	std::vector<D3DXVECTOR3> v1List, v2List;
	int v1Hop, v2Hop;
	D3DXVECTOR3 t1, t2;

	v1Hop = (v1->meshPtr == nullptr) ? 2 : 3;
	v2Hop = (v2->meshPtr == nullptr) ? 2 : 3;

	for (int i = 0; i < v1->indicesCount; i += v1Hop) {

		for (int i_ = 0; i_ < v1Hop; i_++) {

			v1List.push_back(D3DXVECTOR3(
				v1->vertices[v1->indices[i + i_]].x,
				v1->vertices[v1->indices[i + i_]].y,
				v1->vertices[v1->indices[i + i_]].z
				) + v1->pos);
		}

		for (int j = 0; j < v2->indicesCount; j += v2Hop) {

			for (int j_ = 0; j_ < v2Hop; j_++) {
				v2List.push_back(D3DXVECTOR3(
					v2->vertices[v2->indices[j + j_]].x,
					v2->vertices[v2->indices[j + j_]].y,
					v2->vertices[v2->indices[j + j_]].z
					) + v2->pos);
			}

			// v1 list and v2 list now contains the first hop in the indices array
			// checks if the lines intersects on the x and y axis

			if (CM::primitiveCollision(pOut, v1List, v2List))
				return true;

			v2List.clear();
		}

		v1List.clear();
	}

	return false;
}

bool CollisionManager::collideS(VertexShape* v1, VertexShape* v2, D3DXVECTOR3& cV) {
	return false;
}

void CollisionManager::computeAABB(VertexShape* vs) {

	D3DXMATRIX mat;

	vs->max.x = -999; vs->max.y = -999; vs->max.z = -999;
	vs->min.x = +999; vs->min.y = +999; vs->min.z = +999;

	for (int i = 0; i < vs->vertexCount; i++) {

		D3DXMatrixTranslation(&mat, vs->pos.x + vs->vertices[i].x, vs->pos.y + vs->vertices[i].y, vs->pos.z + vs->vertices[i].z);

		if (vs->max.x < mat(3, 0))
			vs->max.x = mat(3, 0);
		if (vs->max.y < mat(3, 1))
			vs->max.y = mat(3, 1);
		if (vs->max.z < mat(3, 2))
			vs->max.z = mat(3, 2);

		if (vs->min.x > mat(3, 0))
			vs->min.x = mat(3, 0);
		if (vs->min.y > mat(3, 1))
			vs->min.y = mat(3, 1);
		if (vs->min.z > mat(3, 2))
			vs->min.z = mat(3, 2);

	}

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
	D3DXVECTOR4					tNorm;
	std::vector<D3DXVECTOR3>	posV;
	std::vector<D3DXVECTOR4>	normV;

	CM::computeAABB(vS);

	rayStart = pStart;
	rayEnd = pEnd;

	// [0] top
	// min.x, max.y	->	max.x, max.y

	tStart.x = vS->min.x;
	tStart.y = vS->max.y;

	tEnd.x = vS->max.x;
	tEnd.y = vS->max.y;

	if (CM::lineSegmentIntersect(intersection, tStart, tEnd, rayStart, rayEnd)) {
		v.x = intersection.x;
		v.y = intersection.y;
		posV.push_back(v);

		dx = tStart.x - tEnd.x;
		dy = tStart.y - tEnd.y;

		tNorm.x = -dy;
		tNorm.y = dx;
		tNorm.z = dy;
		tNorm.w = -dx;

		normV.push_back(tNorm);
	}

	// [1] botom
	// min.x, min.y	->	max.x, min.y

	tStart.x = vS->min.x;
	tStart.y = vS->min.y;

	tEnd.x = vS->max.x;
	tEnd.y = vS->min.y;

	if (CM::lineSegmentIntersect(intersection, tStart, tEnd, rayStart, rayEnd)) {
		v.x = intersection.x;
		v.y = intersection.y;
		posV.push_back(v);

		dx = tStart.x - tEnd.x;
		dy = tStart.y - tEnd.y;

		tNorm.x = -dy;
		tNorm.y = dx;
		tNorm.z = dy;
		tNorm.w = -dx;

		normV.push_back(tNorm);
	}

	// [2] left
	// min.x, max.y	->	min.x, min.y

	tStart.x = vS->min.x;
	tStart.y = vS->max.y;

	tEnd.x = vS->min.x;
	tEnd.y = vS->min.y;

	if (CM::lineSegmentIntersect(intersection, tStart, tEnd, rayStart, rayEnd)) {
		v.x = intersection.x;
		v.y = intersection.y;
		posV.push_back(v);

		dx = tStart.x - tEnd.x;
		dy = tStart.y - tEnd.y;

		tNorm.x = -dy;
		tNorm.y = dx;
		tNorm.z = dy;
		tNorm.w = -dx;

		normV.push_back(tNorm);
	}

	// [3] right
	// max.x, max.y	->	max.x, min.y

	tStart.x = vS->max.x;
	tStart.y = vS->max.y;

	tEnd.x = vS->max.x;
	tEnd.y = vS->min.y;

	if (CM::lineSegmentIntersect(intersection, tStart, tEnd, rayStart, rayEnd)) {
		v.x = intersection.x;
		v.y = intersection.y;
		posV.push_back(v);

		dx = tStart.x - tEnd.x;
		dy = tStart.y - tEnd.y;

		tNorm.x = -dy;
		tNorm.y = dx;
		tNorm.z = dy;
		tNorm.w = -dx;

		normV.push_back(tNorm);
	}

	// the point of intersection will be the one closest to pStart
	// pNorm stores the normal vector

	// only return the closest point of intersection
	for (int i = 0; i < posV.size(); i++) {
		tempVar = P_DIST_2(posV[i], pStart);
		if (tempVar < cDist) {
			cDist = tempVar;
			closest = i;
		}
	}

	if (closest == -1)
		return false;

	pNorm.x = normV[closest].x;
	pNorm.y = normV[closest].y;
	pNorm.z = normV[closest].z;
	pNorm.w = normV[closest].w;

	pOut = posV[closest];
	return true;

}

float CollisionManager::pDist2(const D3DXVECTOR3& p1, const D3DXVECTOR3& p2) {
	return sqrt(pow((float)p1.x - p2.x, 2) + pow((float)p1.y - p2.y, 2));
}

float CollisionManager::pDist3(const D3DXVECTOR3& p1, const D3DXVECTOR3& p2) {
	return sqrt(pow((float)p1.x - p2.x, 2) + pow((float)p1.y - p2.y, 2) + pow((float)p1.z - p1.z, 2));
}

bool CollisionManager::primitiveCollision(D3DXVECTOR3& pOut, std::vector<D3DXVECTOR3>& set1, std::vector<D3DXVECTOR3>& set2) {

	// function to check if 2 sets of vertices collides with each other
	// note that 2 <= n <= 3 for each set of vertices

	for (int i = 0; i < set1.size(); i++) {
		for (int j = 0; j < set2.size(); j++) {
			if (CM::lineSegmentIntersect(pOut, set1[i], set1[(i + 1) % set1.size()], set2[j], set2[(j + 1) % set2.size()]))
				return true;
		}
	}

	return false;

}