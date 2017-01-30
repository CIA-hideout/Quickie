#include "QLine.h"
#include "Player.h"

QLine::QLine(VertexShape* vS, float rotation_) {

	time = 0.5;

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

void QLine::update(float deltaTime, std::vector<VertexShape*>& vS) {
	time -= deltaTime;
	if (time < 0) {
		delete this;
	}
}

void QLine::init(std::vector<VertexShape*>& vS) {

	static int bounceCount = 0;
	// we do not allow the ray to hit the same object more than once per bounce
	int latestID = -1;

	// first trace out the path tha the line will take

	parent->cooldown.at(COOLDOWN_BLINK) = 1.0f;

	D3DXVECTOR3 intersect, fIntersect, rayStart, rayEnd, ts, te, projPoint;
	D3DXVECTOR4 norm;

	float r_, m_ = magnetude;
	float dist_, cDist_;
	rayStart.x = startPoint.x;
	rayStart.y = startPoint.y;
	rayStart.z = 0;
	rayEnd.z = 0;
	int c_;

	vertexPoint.push_back(rayStart);

	while (m_ > 0) {

		if (bounceCount == 0) {

		}
		else {
			printf("bounce [%d]\n", bounceCount);
		}

		rayEnd.x = rayStart.x + cos(rotation_) * m_;
		rayEnd.y = rayStart.y + sin(rotation_) * m_;
		dist_ = cDist_ = 999;

		c_ = 0;

		// >>> [0] scoping down an object, and then ready the ray to hit the next target
		// fIntersect will be the point of intersection for that particular bounce

		for (int i = 0; i < vS.size(); i++) {
			if (vS[i]->objectType == OT_OBS) {
				if (CollisionManager::rayObjectIntersect(intersect, norm, rayStart, rayEnd, vS[i]) && latestID != vS[i]->id) {
					c_++;
					// since rayObjectIntersect already returns the closest point, we can compare each point
					// to see what gets hit first
					dist_ = CollisionManager::pDist2(rayStart, intersect);
					if (cDist_ > dist_) {
						cDist_ = dist_;
						fIntersect = intersect;
						latestID = vS[i]->id;
					}
					// add a vertex into vertexPoint
				}
			}
		}

		if (c_ < 1) {
			// no collisioin detected. probably the end of blink
			vertexPoint.push_back(rayEnd);
			m_ = 0;
		}
		else {
			// this is required if and only if the ray intersects
			printf("point of intersection: %.2f, %.2f\n", fIntersect.x, fIntersect.y);
			vertexPoint.push_back(fIntersect);
			m_ -= cDist_;

			// >>> [0] end

			// get rotation of the norm line segment
			float dx = norm.x - norm.z;
			float dy = norm.y - norm.w;
			r_ = atan(dy / dx);

			// >>> [1] reflecting off a line that has the rotation r_

			// offset raystart by intersect
			rayStart.x -= fIntersect.x;
			rayStart.y -= fIntersect.y;

			projPoint.x = rayStart.x * cos(2 * r_) + rayStart.y * sin(2 * r_);
			projPoint.y = rayStart.x * sin(2 * r_) - rayStart.y * cos(2 * r_);

			// add the offset here
			projPoint.x += fIntersect.x;
			projPoint.y += fIntersect.y;

			// calculate the angle from the point of intersection

			dx = projPoint.x - fIntersect.x;
			dy = projPoint.y - fIntersect.y;

			if (dx > 0) {
				rotation_ = atan(dy / dx);
			}
			else if (dx < 0) {
				rotation_ = PI + atan(dy / dx);
			}
			printf("rotation: %.2f\n", rotation_);

			// >>> [1] end

			// change the start point here
			rayStart.x = fIntersect.x;
			rayStart.y = fIntersect.y;

			printf("ray is now at: %.2f, %.2f", rayStart.x, rayStart.y);
			bounceCount++;
		}


	}

	bounceCount = 0;

	parent->pos.x = vertexPoint[vertexPoint.size() - 1].x;
	parent->pos.y = vertexPoint[vertexPoint.size() - 1].y;

}

void QLine::draw(D3DXMATRIX& worldMat) {

}

QLine::~QLine() {

}
