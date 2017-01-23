#pragma once

#include "graphics.h"
#include "game.h"

enum CollisionType {
	CT_AABB,
	CT_S
};

class VertexShape {

public:

	LPDIRECT3DVERTEXBUFFER9	vertexBuffer;
	LPDIRECT3DINDEXBUFFER9	indexBuffer;
	Graphics*				graphics;
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

