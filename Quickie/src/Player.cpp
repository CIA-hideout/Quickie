#include "Player.h"

int Player::winner = 0;

Player::Player(D3DXVECTOR3& pos, D3DXVECTOR3& dimension, D3DXVECTOR3& scale, D3DXVECTOR3& color) : VertexShape() {

	graphics = nullptr;
	input = nullptr;
	health = maxHealth = 3;

	memcpy(this->pos, pos, sizeof(D3DXVECTOR3));
	memcpy(this->dimension, dimension, sizeof(D3DXVECTOR3));
	memcpy(this->scale, scale, sizeof(D3DXVECTOR3));
	memcpy(this->color, color, sizeof(D3DXVECTOR3));

	min.x = 0;
	min.y = 0;
	min.z = 0;

	rotation.x = 0;
	rotation.y = 0;
	rotation.z = 0;

	objectType = OBJECT_TYPE_PLAYER;

	velocity.x = 0;
	velocity.y = 0;
	velocity.z = 0;

	cooldown.insert(std::pair <CooldownType, float>(COOLDOWN_BLINK, 0.0f));
	cooldown.insert(std::pair <CooldownType, float>(COOLDOWN_TELEPORT, 0.0f));
	cooldown.insert(std::pair <CooldownType, float>(INVULNERABLE, 0.0f));
	cooldown.insert(std::pair <CooldownType, float>(SPAWN_TIME, 0.0f));

	controls.insert(std::pair<Control, int>(CONTROL_UP, 0.1f));
	controls.insert(std::pair<Control, int>(CONTROL_DOWN, 0.1f));
	controls.insert(std::pair<Control, int>(CONTROL_LEFT, 0.1f));
	controls.insert(std::pair<Control, int>(CONTROL_RIGHT, 0.1f));
	controls.insert(std::pair<Control, int>(CONTROL_BL, 0.1f));
	controls.insert(std::pair<Control, int>(CONTROL_TP, 0.1f));

}

void Player::init(Graphics* graphics, Input* input, Audio* audio) {

	this->input = input;
	this->graphics = graphics;
	this->audio = audio;

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

	healthBar = new GUIBar(this, D3DXVECTOR3(217, 83, 79));
	healthBar->init(graphics);
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

		healthBar->draw(worldMat);
	}

	if (!alive) {
		ps.draw(worldMat);
	}

}

void Player::update(float deltaTime, std::vector<VertexShape*>& vS) {

	//printf("%.2f, %.2f\n", pos.x, pos.y);

	for (std::map<CooldownType, float>::iterator i = cooldown.begin(); i != cooldown.end(); i++) {
		if (i->second > 0.0f)
			i->second -= deltaTime;
	}

	if (alive) {

		if (input->getKeyState(controls.at(CONTROL_UP))) {
			velocity.y += deltaTime * playerNS::speed;
		}
		if (input->getKeyState(controls.at(CONTROL_DOWN))) {
			velocity.y -= deltaTime * playerNS::speed;
		}
		if (input->getKeyState(controls.at(CONTROL_LEFT))) {
			velocity.x -= deltaTime * playerNS::speed / ASPECT_RATIO;
		}
		if (input->getKeyState(controls.at(CONTROL_RIGHT))) {
			velocity.x += deltaTime * playerNS::speed / ASPECT_RATIO;
		}

		// blink and tp direction
		if (input->getKeyState(controls.at(CONTROL_BL)) || controlled) {
			if (cooldown.at(COOLDOWN_BLINK) <= 0) {
				if (velocity.x != 0.0f || velocity.y != 0.0f) {
					float r_;
					if (velocity.x >= 0)
						r_ = atan(velocity.y / velocity.x);
					else if (velocity.x < 0)
						r_ = D3DX_PI + atan(velocity.y / velocity.x);
					blink(vS, r_);
				}
			}
		}
		if (input->getKeyState(controls.at(CONTROL_TP)) || controlledTP) {
			if (velocity.x != 0.0f || velocity.y != 0.0f) {
				float r_;
				if (velocity.x >= 0)
					r_ = atan(velocity.y / velocity.x);
				else if (velocity.x < 0)
					r_ = D3DX_PI + atan(velocity.y / velocity.x);

				teleport(vS, r_);
			}
		}

		if (cooldown.at(INVULNERABLE) > 0.0f && timeGetTime() % 500 < 250)
		{
			if (controlled || controlledTP)
			{
			}
			else
				visible = false;
		}
		else
			visible = true;

		if (outOfMap()) {
			die();
		}
	}
	else {
		ps.update(deltaTime, vS);
		if (cooldown.at(SPAWN_TIME) <= 0.0f && health > 0) {
			respawn(vS);
		}
	}

	if (controlled || controlledTP)
		healthBar->visible = false;
	healthBar->percent = (float)health / (float)maxHealth;
	healthBar->scale.x = healthBar->percent;
	healthBar->pos = pos;
	healthBar->pos.y = pos.y + dimension.y;

	velocity.x *= 0.75;
	velocity.y *= 0.75;
	move(vS, deltaTime);
	healthBar->update(deltaTime);
}

void Player::move(std::vector<VertexShape*>& vS, float dt) {

	bool collides;

	// deal with the more predominant velocity

	if (velocity.x >= velocity.y) {
		checkObstaclesCollision(vS, true);			// true, check for x-axis
		checkObstaclesCollision(vS, false);			// false, check for y-axis
	}
	else {
		checkObstaclesCollision(vS, false);			// y
		checkObstaclesCollision(vS, true);			// x
	}

	QLine* qTemp;
	D3DXVECTOR3 poi;

	if (alive) {
		for (int i = 0; i < vS.size(); i++) {
			if (vS[i]->objectType == OBJECT_TYPE_QLINE && vS[i]->alive == true && cooldown.at(INVULNERABLE) <= 0) {
				qTemp = (QLine*)vS[i];
				if (qTemp->parent != this) {
					if (CollisionManager::collidePixelPerfect(poi, this, vS[i])) {
						die();
						break;
					}
				}
			}
			if (vS[i]->objectType == OBJECT_TYPE_WALL && cooldown.at(INVULNERABLE) <= 0) {
				if (CollisionManager::collideAABB(this, vS[i])) {
					die();
					break;
				}
			}
		}
	}

}

void Player::respawn(std::vector<VertexShape*>& vS) {

	D3DXVECTOR2 pos2D = D3DXVECTOR2(randX_2D(), randY_2D());;
	D3DXVECTOR3 pos3D;

	alive = true;
	visible = true;

	graphics->camera->pointInWorld(pos3D, pos2D, playerNS::z);
	pos.x = pos3D.x;
	pos.y = pos3D.y;

	for (int i = 0; i < vS.size(); i++)
	{
		if (vS[i]->id != id && (vS[i]->objectType == OBJECT_TYPE_OBSTACLE))
		{
			if (CollisionManager::collideAABB(this, vS[i]))
			{
				pos2D = D3DXVECTOR2(randX_2D(), randY_2D());
				graphics->camera->pointInWorld(pos3D, pos2D, playerNS::z);
				pos.x = pos3D.x;
				pos.y = pos3D.y;
				i = 0;
			}
		}
	}

	cooldown.at(INVULNERABLE) = 2.0f;
	ps.clean();

}

void Player::blink(std::vector<VertexShape*>& vS, float angle) {

	if (cooldown.at(COOLDOWN_BLINK) <= 0) {

		if (!controlled)
			audio->playCue(FX_BLINK);
		cooldown.at(COOLDOWN_BLINK) = 1.0f;
		QLine* qline = new QLine(this, angle);
		qline->init(vS, graphics);
	}
  
}

void Player::assignControl(rapidjson::Document& doc, int i) {

	controls.at(CONTROL_UP) = doc["player"].GetArray()[i]["up"].GetInt();
	controls.at(CONTROL_DOWN) = doc["player"].GetArray()[i]["down"].GetInt();
	controls.at(CONTROL_LEFT) = doc["player"].GetArray()[i]["left"].GetInt();
	controls.at(CONTROL_RIGHT) = doc["player"].GetArray()[i]["right"].GetInt();
	controls.at(CONTROL_BL) = doc["player"].GetArray()[i]["bl"].GetInt();
	controls.at(CONTROL_TP) = doc["player"].GetArray()[i]["tp"].GetInt();
}

void Player::teleport(std::vector<VertexShape*>& vS, float angle) {

	float magnitude = 10.0f;
	if (cooldown.at(COOLDOWN_TELEPORT) <= 0) {

		if (!controlledTP)
			audio->playCue(FX_TP);

		cooldown.at(COOLDOWN_TELEPORT) = 1.0f;
		pos.x += cos(angle) * magnitude;
		pos.y += sin(angle) * magnitude;
	}
}

void Player::die()
{
	this->alive = false;
	this->visible = false;
	ps = ParticleSource(200, velocity, pos, D3DXVECTOR3(this->color.x, this->color.y, this->color.z), false);
	ps.init(graphics);
	cooldown.at(SPAWN_TIME) = 3.0f;
	graphics->camera->shake(0.25f, 1.0f);

	if (controlledTP || controlled)
	{
	}
	else
	{
		health--;
		audio->playCue(FX_DEATH);
	}
}

void Player::checkObstaclesCollision(std::vector<VertexShape*>& vS, bool x)
{
	if (x)
	{
		this->pos.x += velocity.x;
		for (int i = 0; i < vS.size(); i++) {
			if (vS[i]->id != id && (vS[i]->objectType == OBJECT_TYPE_OBSTACLE)) {
				if (CollisionManager::collideAABB(this, vS[i])) {
					if (velocity.x > 0)
						pos.x = vS[i]->min.x + (this->min.x - this->max.x) / 2 - 0.0001;
					else if (velocity.x < 0)
						pos.x = vS[i]->max.x - (this->min.x - this->max.x) / 2 + 0.0001;
					velocity.x = 0;
				}
			}
		}
	}
	else
	{
		this->pos.y += velocity.y;
		for (int i = 0; i < vS.size(); i++) {
			if (vS[i]->id != id && (vS[i]->objectType == OBJECT_TYPE_OBSTACLE)) {
				if (CollisionManager::collideAABB(this, vS[i])) {
					if (velocity.y > 0)
						pos.y = vS[i]->min.y + (this->min.y - this->max.y) / 2 - 0.0001;
					else if (velocity.y < 0)
						pos.y = vS[i]->max.y - (this->min.y - this->max.y) / 2 + 0.0001;
					velocity.y = 0;
				}
			}
		}
	}
	

}


Player::~Player() {
}
