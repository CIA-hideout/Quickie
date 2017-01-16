#pragma once

#include "VertexShape.h"

class Obstacle : public VertexShape {

private:

public:
	Obstacle() = default;
	Obstacle(D3DXVECTOR3& pos, D3DXVECTOR3& dimension, D3DXVECTOR3& scale, D3DXVECTOR3& color);
	~Obstacle();

	void init(Game*);
	void draw();
	void update(float);
};

