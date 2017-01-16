#pragma once

#include "graphics.h"
#include "game.h"

class VertexShape {

protected:

	LPDIRECT3DVERTEXBUFFER9	vertexBuffer;
	LPDIRECT3DINDEXBUFFER9	indexBuffer;
	Graphics*				graphics;
	int						vertexCount;

	ID3DXMesh*				meshPtr;

	D3DXVECTOR3				pos;
	D3DXVECTOR3				dimension;
	D3DXVECTOR3				scale;

public:

	VertexShape();
	virtual ~VertexShape();

	virtual void init(Game*);
	virtual void draw();
	virtual void update(float);

};

