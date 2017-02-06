#pragma once

#include "Player.h"
#include "CollisionManager.h"

class QLine : public VertexShape {

public:

	float						time;
	float						magnetude;
	float						rotation_;
	VertexShape*				parent;

	std::vector<D3DXVECTOR3>	vertexPoint;

	~QLine();

	QLine(VertexShape*, float);

	D3DXVECTOR3					startPoint;

	void init(std::vector<VertexShape*>&, Graphics*);
	void update(float, std::vector<VertexShape*>&);
	void draw(D3DXMATRIX&);

};

