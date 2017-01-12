#pragma once

#include "VertexShape.h"

class LSquare : public VertexShape{
public:
	LSquare();
	~LSquare();

	void init(Game*);
	void draw(float);
	void update(float);
};

