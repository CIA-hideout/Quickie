#pragma once

#include "Player.h"
#include "CollisionManager.h"

class QLine : public VertexShape {

public:

	float						time;
	float						magnitude;
	float						rotation_;
	VertexShape*				parent;

	std::vector<D3DXVECTOR3>	vertexPoint;

	~QLine();

	QLine(VertexShape*, float, float);

	D3DXVECTOR3					startPoint;

	void init(std::vector<VertexShape*>&, Graphics*);
	void update(float, std::vector<VertexShape*>&);
	void draw(D3DXMATRIX&);

};

