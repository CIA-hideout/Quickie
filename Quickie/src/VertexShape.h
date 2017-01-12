#pragma once

#include "graphics.h"
#include "game.h"

class VertexShape {

protected:

	LPDIRECT3DVERTEXBUFFER9	vertexBuffer;
	LPDIRECT3DINDEXBUFFER9	indexBuffer;
	Graphics*				graphics;
	int						vertexCount;

public:

	VertexShape();
	~VertexShape();

	void init(Game*);
	void draw(float);
	void update(float);

	// TODO: detect colision and transform based on collisions

};

