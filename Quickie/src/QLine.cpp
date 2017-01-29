#include "QLine.h"

QLine::QLine(VertexShape* vS, float rotation_) {

	memcpy(this->startPoint, vS->pos, sizeof(D3DXVECTOR3));

	parent = (Player*)vS;

	this->rotation_ = rotation_;

	CollisionType CT_OOBB;

	LVertex lV = LVertex();
	lV.x = startPoint.x;
	lV.y = startPoint.y;
	lV.z = startPoint.z;

	vertices[0] = lV;

}

void QLine::init(std::vector<VertexShape*>& vS) {

	// first trace out the path tha the line will take

	float tempM = magnetude;
	float tempI, cIntersection = 999;

	D3DXVECTOR3 currPoint, rayStart, rayEnd, tStart, tEnd, intersection, fIntersection;
	D3DXVECTOR4 normal, fNormal;
	std::vector<D3DXVECTOR3> posV;

	currPoint = startPoint;
	rayStart = startPoint;

	while (tempM > 0) {

		rayEnd.x = rayStart.x + cos(rotation_) * tempM;
		rayEnd.y = rayStart.y + sin(rotation_) * tempM;
		rayEnd.z = 0;

		for (int i = 0; i < vS.size(); i++) {
			if (vS[i]->objectType == OT_OBS) {
				tempI = CollisionManager::rayObjectIntersect(intersection, normal, rayStart, rayEnd, vS[i]);
				if (tempI < cIntersection) {
					cIntersection = tempI;
					fIntersection = intersection;
					fNormal = normal;
				}
			}
		}

		vertexPoint.push_back(fIntersection);
		
		tempM -= cIntersection;
		rayStart = fIntersection;
	}

	parent->pos = rayEnd;

}

QLine::~QLine() {

}
