#include "Player.h"
#include "QLine.h"

Player::Player(D3DXVECTOR3& pos, D3DXVECTOR3& dimension, D3DXVECTOR3& scale, D3DXVECTOR3& color) : VertexShape() {

	graphics = nullptr;
	input = nullptr;
	static int playerCount = 0;
	playerId = playerCount++;
	health = 3;

	memcpy(this->pos, pos, sizeof(D3DXVECTOR3));
	memcpy(this->dimension, dimension, sizeof(D3DXVECTOR3));
	memcpy(this->scale, scale, sizeof(D3DXVECTOR3));
	memcpy(this->color, color, sizeof(D3DXVECTOR3));

	min.x = 0;
	min.y = 0;
	min.z = 0;

	min.x = 0;
	min.y = 0;
	min.z = 0;

	rotation.x = 0;
	rotation.y = 0;
	rotation.z = 0;

	collisionType = CT_AABB;
	objectType = OT_PLY;

	velocity.x = 0;
	velocity.y = 0;
	velocity.z = 0;

	cooldown.insert(std::pair <CooldownType, float>(COOLDOWN_BLINK, 0.0f));
	cooldown.insert(std::pair <CooldownType, float>(COOLDOWN_TELEPORT, 0.0f));

	controls.insert(std::pair<Control, int>(CONTROL_UP, 0.1f));
	controls.insert(std::pair<Control, int>(CONTROL_DOWN, 0.1f));
	controls.insert(std::pair<Control, int>(CONTROL_LEFT, 0.1f));
	controls.insert(std::pair<Control, int>(CONTROL_RIGHT, 0.1f));
	controls.insert(std::pair<Control, int>(CONTROL_BL, 0.1f));
	controls.insert(std::pair<Control, int>(CONTROL_TP, 0.1f));

}

void Player::init(Graphics* g, Input* i) {

	graphics = g;
	input = i;

	D3DXCreateMeshFVF(12, 24, D3DXMESH_MANAGED, CUSTOMFVF, graphics->get3Ddevice(), &meshPtr);

	meshPtr->LockVertexBuffer(0, (void**)&vertices);

	// 0
	vertices[0] = { -dimension.x / ASPECT_RATIO / 2, -dimension.y / 2, -dimension.z / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(color.x), (int)(color.y), (int)(color.z)) };
	// 1						 												    
	vertices[1] = { -dimension.x / ASPECT_RATIO / 2, +dimension.y / 2, -dimension.z / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(color.x), (int)(color.y), (int)(color.z)) };
	// 2						 												    
	vertices[2] = { +dimension.x / ASPECT_RATIO / 2, +dimension.y / 2, -dimension.z / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(color.x), (int)(color.y), (int)(color.z)) };
	// 3						 												    
	vertices[3] = { +dimension.x / ASPECT_RATIO / 2, -dimension.y / 2, -dimension.z / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(color.x), (int)(color.y), (int)(color.z)) };
	// 4						 												    
	vertices[4] = { -dimension.x / ASPECT_RATIO / 2, -dimension.y / 2, +dimension.z / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(color.x), (int)(color.y), (int)(color.z)) };
	// 5						 												    
	vertices[5] = { -dimension.x / ASPECT_RATIO / 2, +dimension.y / 2, +dimension.z / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(color.x), (int)(color.y), (int)(color.z)) };
	// 6						 												    
	vertices[6] = { +dimension.x / ASPECT_RATIO / 2, +dimension.y / 2, +dimension.z / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(color.x), (int)(color.y), (int)(color.z)) };
	// 7						 												    
	vertices[7] = { +dimension.x / ASPECT_RATIO / 2, -dimension.y / 2, +dimension.z / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(color.x), (int)(color.y), (int)(color.z)) };

	meshPtr->UnlockVertexBuffer();

	vertexCount = 8;

	meshPtr->LockIndexBuffer(0, (void**)&indices);

	// front
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;
	// back
	indices[6] = 4; indices[7] = 6; indices[8] = 5;
	indices[9] = 4; indices[10] = 7; indices[11] = 6;
	// left
	indices[12] = 4; indices[13] = 5; indices[14] = 1;
	indices[15] = 4; indices[16] = 1; indices[17] = 0;
	// right
	indices[18] = 3; indices[19] = 2; indices[20] = 6;
	indices[21] = 3; indices[22] = 6; indices[23] = 7;
	// top
	indices[24] = 1; indices[25] = 5; indices[26] = 6;
	indices[27] = 1; indices[28] = 6; indices[29] = 2;
	// bottom
	indices[30] = 4; indices[31] = 0; indices[32] = 3;
	indices[33] = 4; indices[34] = 3; indices[35] = 7;

	meshPtr->UnlockIndexBuffer();

	indicesCount = 36;

	visible = true;
	alive = true;

}

void Player::draw(D3DXMATRIX& worldMat) {

	if (visible) {
		LPDIRECT3DVERTEXBUFFER9 vBuffer;
		LPDIRECT3DINDEXBUFFER9 iBuffer;
		meshPtr->GetVertexBuffer(&vBuffer);
		meshPtr->GetIndexBuffer(&iBuffer);
		this->graphics->get3Ddevice()->SetStreamSource(0, vBuffer, 0, sizeof(LVertex));
		this->graphics->get3Ddevice()->SetIndices(iBuffer);

		D3DXMatrixRotationYawPitchRoll(&matRot, rotation.y, rotation.z, rotation.x);
		D3DXMatrixTranslation(&worldMat, pos.x, pos.y, pos.z);

		this->graphics->get3Ddevice()->SetTransform(D3DTS_WORLD, &(matRot * worldMat));
		meshPtr->DrawSubset(0);
	}

}

void Player::update(float deltaTime, std::vector<VertexShape*>& vS) {

	if (alive) {
		if (input->getKeyState(controls.at(CONTROL_UP))) {
			velocity.y += deltaTime * 10;
		}
		if (input->getKeyState(controls.at(CONTROL_DOWN))) {
			velocity.y -= deltaTime * 10;
		}
		if (input->getKeyState(controls.at(CONTROL_LEFT))) {
			velocity.x -= deltaTime * 10 / ASPECT_RATIO;
		}
		if (input->getKeyState(controls.at(CONTROL_RIGHT))) {
			velocity.x += deltaTime * 10 / ASPECT_RATIO;
		}

		// blink and tp direction
		if (input->getKeyState(controls.at(CONTROL_BL))) {
			if (cooldown.at(COOLDOWN_BLINK) <= 0) {
				cooldown.at(COOLDOWN_BLINK) = 1.0f;
				float r_;
				if (velocity.x >= 0)
					r_ = atan(velocity.y / velocity.x);
				else if (velocity.x < 0)
					r_ = D3DX_PI + atan(velocity.y / velocity.x);

				blink(vS, r_);
			}
		}

		for (std::map<CooldownType, float>::iterator i = cooldown.begin(); i != cooldown.end(); i++) {
			if (i->second > 0.0f)
				i->second -= deltaTime;
		}

		velocity.x *= 0.75;
		velocity.y *= 0.75;
		move(vS, deltaTime);
	}
}

void Player::move(std::vector<VertexShape*>& vS, float dt) {
	bool collides;
	this->pos.x += velocity.x;
	for (int i = 0; i < vS.size(); i++) {
		if (vS[i]->id != id && vS[i]->objectType == OT_OBS) {
			if (CollisionManager::collideAABB(this, vS[i])) {
				if (velocity.x > 0)
					pos.x = vS[i]->min.x + (this->min.x - this->max.x) / 2 - 0.0001;
				else if (velocity.x < 0)
					pos.x = vS[i]->max.x - (this->min.x - this->max.x) / 2 + 0.0001;
				velocity.x = 0;
			}
		}
	}

	this->pos.y += velocity.y;
	for (int i = 0; i < vS.size(); i++) {
		if (vS[i]->id != id && vS[i]->objectType == OT_OBS) {
			if (CollisionManager::collideAABB(this, vS[i])) {
				if (velocity.y > 0)
					pos.y = vS[i]->min.y + (this->min.y - this->max.y) / 2 - 0.0001;
				else if (velocity.y < 0)
					pos.y = vS[i]->max.y - (this->min.y - this->max.y) / 2 + 0.0001;
				velocity.y = 0;
			}
		}
	}

	QLine* qTemp;
	D3DXVECTOR3 poi;

	for (int i = 0; i < vS.size(); i++) {
		if (vS[i]->objectType == OT_QL && vS[i]->alive == true) {
			qTemp = (QLine*)vS[i];
			if (qTemp->parent != this) {
				if (CollisionManager::collidePixelPerfect(poi, this, vS[i])) {

					// collision happened
					this->visible = false;

					// add this to a list of things to be deleted or something
					this->alive = false;

				}
			}
		}
	}
}

void Player::respawn() {
	if (pos.y <= -25) {
		pos.y = 20;
	}

	if (pos.x < -20) {
		pos.x = 20;
	}

	if (pos.x > 20){
		pos.x = -20;
	}
}

void Player::blink(std::vector<VertexShape*>& vS, float angle) {

	velocity *= 0;
	QLine* l = new QLine(this, angle);
	l->init(vS, graphics);

}

void Player::assignControl(rapidjson::Document& doc) {

	controls.at(CONTROL_UP) = doc["control"].GetArray()[playerId]["up"].GetInt();
	controls.at(CONTROL_DOWN) = doc["control"].GetArray()[playerId]["down"].GetInt();
	controls.at(CONTROL_LEFT) = doc["control"].GetArray()[playerId]["left"].GetInt();
	controls.at(CONTROL_RIGHT) = doc["control"].GetArray()[playerId]["right"].GetInt();
	controls.at(CONTROL_BL) = doc["control"].GetArray()[playerId]["bl"].GetInt();
	controls.at(CONTROL_TP) = doc["control"].GetArray()[playerId]["tp"].GetInt();

}

Player::~Player() {
}
