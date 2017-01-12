#pragma once

#include "VertexShape.h"

class LTriangle : public VertexShape {

private:

public:

	LTriangle();
	~LTriangle();

	void init(Game*);
	void draw(float);
	void update(float);

};
