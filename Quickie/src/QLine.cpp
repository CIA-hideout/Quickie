#include "QLine.h"
#include "Player.h"

QLine::QLine(VertexShape* vS, float rotation_) {

	memcpy(this->startPoint, vS->pos, sizeof(D3DXVECTOR3));

	parent = (Player*)vS;

	this->rotation_ = rotation_;

	magnetude = 10;

	CollisionType CT_OOBB;

	LVertex lV = LVertex();
	lV.x = startPoint.x;
	lV.y = startPoint.y;
	lV.z = startPoint.z;

}

void QLine::init(std::vector<VertexShape*>& vS) {

	// first trace out the path tha the line will take

	parent->cooldown.at(COOLDOWN_BLINK) = 5.0f;

	float tempM = magnetude;
	float tempI, cIntersection = 999;
	bool collides;

	D3DXVECTOR3 currPoint, rayStart, rayEnd, tStart, tEnd, intersection, fIntersection;
	D3DXVECTOR4 normal, fNormal;
	std::vector<D3DXVECTOR3> posV;

	currPoint = startPoint;
	rayStart = startPoint;

	vertexPoint.push_back(startPoint);

	while (tempM > 0) {

		rayEnd.x = rayStart.x + cos(rotation_) * tempM;
		rayEnd.y = rayStart.y + sin(rotation_) * tempM;
		rayEnd.z = 0;

		for (int i = 0; i < vS.size(); i++) {
			if (vS[i]->objectType == OT_OBS) {
				collides = CollisionManager::rayObjectIntersect(intersection, normal, rayStart, rayEnd, vS[i]);
				if (collides) {
					printf("collided\n");
					tempI = CollisionManager::pDist2(rayStart, intersection);
					if (tempI < cIntersection) {
						cIntersection = tempI;
						fIntersection = intersection;
						fNormal = normal;
					}
				}
			}
		}

		vertexPoint.push_back(fIntersection);
		// reduce the magnitude by the distance it has just travelled
		tempM -= cIntersection;
		// set starting point where the ray has left off
		rayStart = fIntersection;
	}

	// checks if there are any reflections. If no, the blink path is clear
	if (vertexPoint.size() == 2) {
		fIntersection.x = rayEnd.x;
		fIntersection.y = rayEnd.y;
	}

	parent->pos.x = fIntersection.x;
	parent->pos.y = fIntersection.y;

}

QLine::~QLine() {

}
