#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

#include "VertexShape.h"
#include "Player.h"
#include "Obstacle.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

class CollisionManager {

public:

	std::vector<VertexShape*>	entityPool;

	CollisionManager();
	~CollisionManager();

	void addEntity(VertexShape*);
	void removeEntity(VertexShape*);

	void checkCollision(std::vector<VertexShape*>&);
	void checkCollision(VertexShape*, std::vector<VertexShape*>&);

	float calcDistance(D3DXVECTOR3&, D3DXVECTOR3&);
	
	static bool collideAABB(VertexShape*, VertexShape*);
	static bool collideOOBB(VertexShape*, VertexShape*, D3DXVECTOR3&);
	static bool collideS(VertexShape*, VertexShape*, D3DXVECTOR3&);

	static void computeAABB(VertexShape*, D3DXVECTOR3&, D3DXVECTOR3&);
	static void computeOOBB(VertexShape*, D3DXVECTOR3&, D3DXVECTOR3&, D3DXMATRIX&);

};