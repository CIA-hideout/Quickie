#include "QLine.h"
#include "Player.h"

QLine::QLine(VertexShape* vS, float rotation_) : VertexShape() {

	time = 0.5;

	memcpy(this->startPoint, vS->pos, sizeof(D3DXVECTOR3));

	parent = vS;

	this->rotation_ = rotation_;

	magnetude = 20;

	objectType = OT_QL;
	collisionType = CT_OOBB;

	meshPtr = nullptr;

	color = parent->color;

}

void QLine::update(float deltaTime, std::vector<VertexShape*>& vS) {
	time -= deltaTime;
	if (time < 0) {
		alive = false;
		visible = false;
	}
	
	//D3DXVECTOR3 intersect;

	//for (int i = 0; i < vS.size(); i++) {
	//	if (vS[i]->objectType == OT_QL && vS[i]->alive == true) {
	//		if (CollisionManager::collidePixelPerfect(intersect, this, vS[i])) {
	//			if (vS[i]->id > id) {
	//				QLine* qtemp = (QLine*)vS[i];
	//				Player* ptemp = (Player*)qtemp->parent;
	//				ptemp->alive = false;
	//				ptemp->visible = false;
	//				ptemp->ps = ParticleSource(100, parent->velocity, pos, this->color);

	//				ptemp->ps.init(game);
	//				ptemp->cooldown.at(SPAWN_TIME) = 3.0f;
	//				qtemp->alive = false;
	//				ptemp->pos = intersect;
	//			}
	//		}
	//		else {
	//			printf("does not intersect\n");
	//		}
	//	}
	//}

}

void QLine::init(std::vector<VertexShape*>& vS, Graphics* graphics) {

	D3DXVECTOR3 intersect, fIntersect, rayStart, rayEnd, ts, te, projPoint;
	D3DXVECTOR4 norm, fNorm;

	this->graphics = graphics;

	float r_, m_ = magnetude;
	float dist_, cDist_;
	rayStart.x = startPoint.x;
	rayStart.y = startPoint.y;
	rayStart.z = 0;
	rayEnd.z = 0;
	int c_, latestID, fLatestID;

	fLatestID = latestID = -1;

	vertexPoint.push_back(rayStart);

	while (m_ > 0) {

		rayEnd.x = rayStart.x + cos(rotation_) * m_;
		rayEnd.y = rayStart.y + sin(rotation_) * m_;
		dist_ = cDist_ = 999;

		c_ = 0;

		// >>> [0] scoping down an object, and then ready the ray to hit the next target
		// fIntersect will be the point of intersection for that particular bounce

		for (int i = 0; i < vS.size(); i++) {
			if (vS[i]->objectType == OT_OBS) {
				if (CollisionManager::rayObjectIntersect(intersect, norm, rayStart, rayEnd, vS[i]) && fLatestID != vS[i]->id) {
					c_++;
					// since rayObjectIntersect already returns the closest point, we can compare each point
					// to see what gets hit first
					dist_ = CollisionManager::pDist2(rayStart, intersect);
					if (cDist_ > dist_) {
						cDist_ = dist_;
						fIntersect = intersect;
						latestID = vS[i]->id;
						fNorm = norm;
					}
					// add a vertex into vertexPoint
				}
			}
		}

		fLatestID = latestID;

		if (c_ < 1) {
			// no collisioin detected. probably the end of blink
			vertexPoint.push_back(rayEnd);
			m_ = 0;
		}
		else {
			// this is required if and only if the ray intersects
			vertexPoint.push_back(fIntersect);
			m_ -= cDist_;

			// >>> [0] end

			// get rotation of the norm line segment
			float dx = fNorm.x - fNorm.z;
			float dy = fNorm.y - fNorm.w;
			r_ = atan(dy / dx);

			// >>> [1] reflecting off a line that has the rotation r_

			// translate raystart
			rayStart.x -= fIntersect.x;
			rayStart.y -= fIntersect.y;

			projPoint.x = rayStart.x * cos(2 * r_) + rayStart.y * sin(2 * r_);
			projPoint.y = rayStart.x * sin(2 * r_) - rayStart.y * cos(2 * r_);

			// translate projection point back
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

			// >>> [1] end

			// change the start point here
			rayStart.x = fIntersect.x;
			rayStart.y = fIntersect.y;
		}
	}

	parent->pos.x = vertexPoint[vertexPoint.size() - 1].x;
	parent->pos.y = vertexPoint[vertexPoint.size() - 1].y;

	vertexCount = vertexPoint.size();

	// no need for meshes here. lines can be rendered with primitive indices
	vertices = 0;

	graphics->get3Ddevice()->CreateVertexBuffer(
		sizeof(LVertex)* vertexCount,
		D3DUSAGE_WRITEONLY,
		CUSTOMFVF,
		D3DPOOL_MANAGED,
		&vertexBuffer,
		0
		);

	graphics->get3Ddevice()->CreateIndexBuffer(
		(vertexCount * 2 - 2) * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&indexBuffer,
		0
		);

	vertexBuffer->Lock(0, 0, (void**)&vertices, 0);

	for (int i = 0; i < vertexCount; i++) {
		LVertex v_;
		v_.x = vertexPoint[i].x - startPoint.x;
		v_.y = vertexPoint[i].y - startPoint.y;
		v_.z = 0;
		v_.color = D3DCOLOR_ARGB(255, (int)parent->color.x, (int)parent->color.y, (int)parent->color.z);
		vertices[i] = v_;
	}

	vertexBuffer->Unlock();

	indexBuffer->Lock(0, 0, (void**)&indices, 0);

	indicesCount = vertexCount * 2 - 2;

	for (int i = 0; i < indicesCount; i++) {
		indices[i] = (i + 1) / 2;
	}

	indexBuffer->Unlock();

	this->alive = true;
	this->visible = true;

	pos = startPoint;

	vS.push_back(this);

}

void QLine::draw(D3DXMATRIX& worldMat) {

	if (visible) {
		D3DXMatrixTranslation(&matTrans, startPoint.x, startPoint.y, parent->pos.z);

		graphics->get3Ddevice()->SetTransform(D3DTS_WORLD, &matTrans);

		graphics->get3Ddevice()->SetStreamSource(0, vertexBuffer, 0, sizeof(LVertex));
		graphics->get3Ddevice()->SetIndices(indexBuffer);
		graphics->get3Ddevice()->SetFVF(CUSTOMFVF);
		graphics->get3Ddevice()->DrawIndexedPrimitive(D3DPT_LINELIST, 0, 0, vertexCount, 0, vertexCount - 1);
	}
}

QLine::~QLine() {

}
