#pragma once

#include "VertexShape.h"
#include "Obstacle.h"

class Player : public VertexShape {
public:

	Obstacle*	onPlatform;
	bool		canJump;

	Player() = default;
	~Player();

	Player(D3DXVECTOR3& pos, D3DXVECTOR3& dimension, D3DXVECTOR3& scale, D3DXVECTOR3& color);

	void init(Game*);
	void draw(D3DXMATRIX&);
	void update(float);
};

