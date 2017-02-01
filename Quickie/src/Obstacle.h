#pragma once

#include "VertexShape.h"

class Obstacle : public VertexShape {

private:
	int obstacleId;
	int spawnMinX;
	int spawnMaxX;
	float timer = 0;		// a timer to move/change direction

public:
	Obstacle() = default;
	Obstacle(D3DXVECTOR3& pos, D3DXVECTOR3& dimension, D3DXVECTOR3& scale, D3DXVECTOR3& color);
	Obstacle(const int[]);
	~Obstacle();

	void init(Game*);
	void draw(D3DXMATRIX&);
	void update(float);
	void setColor(D3DXVECTOR3);
	void setDimension(D3DXVECTOR3);
	void setPosition(D3DXVECTOR3);
	D3DXVECTOR3 getRandomColor();
	D3DXVECTOR3 getRandomDimension();

	//void assignPosition
};
