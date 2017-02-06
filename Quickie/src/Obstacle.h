#pragma once

#include "VertexShape.h"
#include "CollisionManager.h"

enum ObsState
{
	INACTIVE,
	ACTIVE,
	SHRINK,
	GROW
};

class Obstacle : public VertexShape {

private:
	int obstacleId;
	int spawnMinX;
	int spawnMaxX;
	float timer = 0;			// a timer to move/change direction
	boolean isRandom = false;
	int currentState = INACTIVE;

	D3DXVECTOR3 lvl1Pos;
	D3DXVECTOR3 lvl1Dim;
	D3DXVECTOR3 lvl2Pos;
	D3DXVECTOR3 lvl2Dim;
	D3DXVECTOR3 lvl3Pos;
	D3DXVECTOR3 lvl3Dim;

	D3DXVECTOR3 newPos;			// store the new position when updating
	D3DXVECTOR3 newDimension;	// store the new dimension

public:
	Obstacle() = default;
	Obstacle(D3DXVECTOR3& pos, D3DXVECTOR3& dimension, D3DXVECTOR3& scale, D3DXVECTOR3& color);
	~Obstacle();

	void init(Audio*, Graphics*);
	void draw(D3DXMATRIX&);
	void update(float, std::vector<VertexShape*>);
	void setColor(D3DXVECTOR3);
	void setDimension(D3DXVECTOR3);
	void setPosition(D3DXVECTOR3);
	D3DXVECTOR3 getRandomColor();
	D3DXVECTOR3 getRandomDimension();

	// set Levels location
	void setLevel1(int);
	void setLevel2(int);
	void setLevel3(int);

	// assign position from json
	void assignPosition(rapidjson::Document&, int obstacle);
	D3DXVECTOR3 assignDimension(int);
};
