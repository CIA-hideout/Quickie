#pragma once

#include "VertexShape.h"
#include "CollisionManager.h"

#ifndef _PARTICLE_SOURCE_
#define _PARTICLE_SOURCE_

class ParticleSource : public VertexShape {

public:

	ParticleSource();
	ParticleSource(int, float, D3DXVECTOR3&, D3DXVECTOR3&);
	~ParticleSource();

	int							particleCount;
	float						direction, duration;
	std::vector<VertexShape*>	particles;

	void init(Game*);
	void draw(D3DXMATRIX&);
	void update(float, std::vector<VertexShape*>&);
	void move(std::vector<VertexShape*>&, float);

	void clean();

};

#endif