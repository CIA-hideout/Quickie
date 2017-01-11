#pragma once

#include "graphics.h"
#include "game.h"

class LTriangle {

private:

	LPDIRECT3DVERTEXBUFFER9	vertexBuffer;
	Graphics*				graphics;

public:

	LTriangle();
	~LTriangle();

	void init(Game* gamePtr);
	void draw();
	void update(float);

};

