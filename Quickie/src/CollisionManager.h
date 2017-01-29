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

#define C_CT_AABB_AABB(v1, v2)	(v1->collisionType == CT_AABB && v2->collisionType == CT_AABB)
#define C_CT_OOBB_OOBB(v1, v2)	(v1->collisionType == CT_OOBB && v2->collisionType == CT_OOBB)
#define C_CT_S_S(v1, v2)		(v1->collisionType == CT_S && v2->collisionType == CT_S)

#define P_DIST_3(p1, p2)		sqrt(pow((float)p1.x - p2.x, 2) + pow((float)p1.y - p2.y, 2) + pow((float)p1.z - p1.z, 2))
#define P_DIST_2(p1, p2)		sqrt(pow((float)p1.x - p2.x, 2) + pow((float)p1.y - p2.y, 2))

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