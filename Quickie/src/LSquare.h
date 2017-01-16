#pragma once

#include "VertexShape.h"

class LSquare : public VertexShape{
public:
	LSquare();
	~LSquare();

	void init(Game*);
	void draw();
	void update(float);
};

