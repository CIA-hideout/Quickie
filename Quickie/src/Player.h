#pragma once

#include "VertexShape.h"
#include "Obstacle.h"
#include "CollisionManager.h"

enum CooldownType {
	COOLDOWN_BLINK,
	COOLDOWN_TELEPORT
};

class Player : public VertexShape {
public:

	bool							canJump;

	bool							canTeleport;
	std::map<CooldownType, float>	cooldown;

	Player() = default;
	~Player();

	Player(D3DXVECTOR3& pos, D3DXVECTOR3& dimension, D3DXVECTOR3& scale, D3DXVECTOR3& color);

	void init(Game*);
	void draw(D3DXMATRIX&);
	void update(float, std::vector<VertexShape*>&);
	void moveX(float&);
	void moveY(float&);
	void moveZ(float&);
	void move(std::vector<VertexShape*>& vS, float);

};

