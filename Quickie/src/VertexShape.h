#pragma once

#include "graphics.h"
#include "game.h"
#include "CollisionManager.h"

enum CollisionType {
	CT_AABB,
	CT_OOBB,
	CT_S,
	CT_N
};

enum ObjectType {
	OT_PLY,
	OT_OBS,
	OT_QL
};

class VertexShape {

public:

	LPDIRECT3DVERTEXBUFFER9	vertexBuffer;
	LPDIRECT3DINDEXBUFFER9	indexBuffer;
	Game*					game;
	int						vertexCount;

	ID3DXMesh*				meshPtr;

	D3DXVECTOR3				pos;
	D3DXVECTOR3				dimension;
	D3DXVECTOR3				scale;
	D3DXVECTOR3				color;
	D3DXVECTOR3				rotation;

	LVertex*				vertices;
	WORD*					indices;

	D3DXVECTOR3*			center;
	D3DXVECTOR3				min;
	D3DXVECTOR3				max;
	D3DXVECTOR3				velocity;
	float					radius;

	float					mass;

	CollisionType			collisionType;
	ObjectType				objectType;

	int						id;

public:

	VertexShape();
	virtual ~VertexShape();

	virtual void init(Game*);
	virtual void draw(D3DXMATRIX&);
	virtual void update(float);

	void computeBoundingBox();
	void computeBoundingSphere();
	bool collidesWith(VertexShape&);

};

