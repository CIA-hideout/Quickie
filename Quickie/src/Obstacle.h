#pragma once

#include "VertexShape.h"

class Obstacle : public VertexShape {

private:

public:
	Obstacle() = default;
	Obstacle(D3DXVECTOR3& pos, D3DXVECTOR3& dimension, D3DXVECTOR3& scale, D3DXVECTOR3& color);
	Obstacle(D3DXVECTOR3& pos);
	~Obstacle();

	void init(Game*);
	void draw(D3DXMATRIX&);
	void update(float);
	void setColor(D3DXVECTOR3);
	D3DXVECTOR3 getRandomColor();
	D3DXVECTOR3 setDimension();
};
