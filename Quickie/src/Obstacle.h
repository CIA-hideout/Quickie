#pragma once

#include "VertexShape.h"

class Obstacle : public VertexShape {

private:
	// color RGB for D3DXVECTOR3
	D3DXVECTOR3 COLOR_RED = D3DXVECTOR3(255, 0, 0);
	D3DXVECTOR3 COLOR_YELLOW = D3DXVECTOR3(255, 255, 0);
	D3DXVECTOR3 COLOR_PURPLE = D3DXVECTOR3(255, 0, 255);
	D3DXVECTOR3 COLOR_GREEN = D3DXVECTOR3(0, 255, 0);
	D3DXVECTOR3 COLOR_BLUE = D3DXVECTOR3(0, 0, 255);
	D3DXVECTOR3 COLOR_WHITE = D3DXVECTOR3(255, 255, 255);

	// Dimensions of Obstructor
	D3DXVECTOR3 DIMENSTION_SMALL = D3DXVECTOR3(7, 1, 2.5);		// small destructor
	D3DXVECTOR3 DIMENSTION_MEDIUM = D3DXVECTOR3(10, 1, 2.5);	// long destructor


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
