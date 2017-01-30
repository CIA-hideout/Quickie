#pragma once

#include "VertexShape.h"
#include "CollisionManager.h"

class QLine : public VertexShape {

public:

	float						time;
	float						magnetude;
	float						rotation_;
	int							id;
	Player*						parent;
	
	std::vector<D3DXVECTOR3>	vertexPoint;

	QLine() = default;
	~QLine();

	QLine(VertexShape*, float);

	D3DXVECTOR3				startPoint;

	void init(std::vector<VertexShape*>&);
	void update(float, std::vector<VertexShape*>&);
	void draw(D3DXMATRIX&);
	
};


