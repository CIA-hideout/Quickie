#pragma once
#include "VertexShape.h"

namespace nodeNS
{
	const int length = 2;
	const int breadth = 2;
	const int height = 2;
	const int z = 19.5;
}

class Node : public VertexShape
{
protected:
	bool active = false;			// active represents a filled space

public:
	Node() = default;
	Node(D3DXVECTOR3& pos, D3DXVECTOR3& dimension, D3DXVECTOR3& scale, D3DXVECTOR3& color);
	virtual ~Node();

	void init(Graphics*);
	void draw(D3DXMATRIX&);
	void update(float);
};