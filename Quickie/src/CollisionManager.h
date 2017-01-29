#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

#include "VertexShape.h"
#include "Player.h"
#include "Obstacle.h"
#include <algorithm>
#include <functional>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

class CollisionManager {

public:

	std::vector<VertexShape*>	entityPool;

	CollisionManager();
	~CollisionManager();

	void checkCollision(VertexShape*, std::vector<VertexShape*>&);

	float calcDistance(D3DXVECTOR3&, D3DXVECTOR3&);

	static bool collideAABB(VertexShape*, VertexShape*);
	static bool collideOOBB(VertexShape*, VertexShape*, D3DXVECTOR3&);
	static bool collideS(VertexShape*, VertexShape*, D3DXVECTOR3&);

	static void computeAABB(VertexShape*);
	static void computeOOBB(VertexShape*, D3DXVECTOR3&, D3DXVECTOR3&, D3DXMATRIX&);

	static bool rayObjectIntersect(D3DXVECTOR3&, D3DXVECTOR4&, D3DXVECTOR3&, D3DXVECTOR3&, VertexShape*);
	static bool lineSegmentIntersect(D3DXVECTOR3& pOut, D3DXVECTOR3& pStart, D3DXVECTOR3& pEnd, D3DXVECTOR3& qStart, D3DXVECTOR3& qEnd);
	static float counterClockwise(D3DXVECTOR3& p, D3DXVECTOR3& q, D3DXVECTOR3& r);

	static float pDist3(const D3DXVECTOR3&, const D3DXVECTOR3&);
	static float pDist2(const D3DXVECTOR3&, const D3DXVECTOR3&);


};