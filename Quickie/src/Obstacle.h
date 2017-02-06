#pragma once

#include "VertexShape.h"

class Obstacle : public VertexShape {
private:
	int obstacleId;
	int spawnMinX;
	int spawnMaxX;
	float timer = 0;		// a timer to move/change direction
	boolean isRandom = false;

	D3DXVECTOR3 lvl1Pos;
	D3DXVECTOR3 lvl1Dim;
	D3DXVECTOR3 lvl2Pos;
	D3DXVECTOR3 lvl2Dim;
	D3DXVECTOR3 lvl3Pos;
	D3DXVECTOR3 lvl3Dim;

public:
	Obstacle() = default;
	Obstacle(D3DXVECTOR3& pos, D3DXVECTOR3& dimension, D3DXVECTOR3& scale, D3DXVECTOR3& color);
	Obstacle(const int[]);
	~Obstacle();

	void init(Graphics*);
	void draw(D3DXMATRIX&);
	void update(float);
	void setColor(D3DXVECTOR3);
	void setDimension(D3DXVECTOR3);
	void setPosition(D3DXVECTOR3);
	D3DXVECTOR3 getRandomColor();
	D3DXVECTOR3 getRandomDimension();

	// set Levels location
	void setLevel1();
	void setLevel2();
	void setLevel3();

	// assign position from json
	void assign(rapidjson::Document&);
	D3DXVECTOR3 assignDimension(int);
};
