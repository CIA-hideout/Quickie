#pragma once

#include "VertexShape.h"
#include "CollisionManager.h"
#include "Random.h"

#ifndef _PARTICLE_SOURCE_
#define _PARTICLE_SOURCE_

struct ParticleData {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 velocity;
};

class ParticleSource : public VertexShape {

public:

	ParticleSource();
	ParticleSource(int, D3DXVECTOR3&, D3DXVECTOR3&, D3DXVECTOR3&, bool inherit = true);
	~ParticleSource();

	int							particleCount;
	float						direction, duration;
	VertexShape*				vShape;
	ParticleData*				particles;
	bool						inherit;

	void init(Graphics*);
	void draw(D3DXMATRIX&);
	void update(float, std::vector<VertexShape*>&);
	void move(std::vector<VertexShape*>&, float);

	void clean();

};

#endif