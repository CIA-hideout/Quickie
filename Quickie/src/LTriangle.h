#pragma once

#include "VertexShape.h"

class LTriangle : public VertexShape {

private:

public:

	LTriangle();
	~LTriangle();

	void init(Game*);
	void draw();
	void update(float);

};
