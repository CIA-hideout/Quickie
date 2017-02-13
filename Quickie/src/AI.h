#pragma once

#include "ParticleSource.h"
#include "QLine.h"
#include "GUIBar.h"
#include "random.h"

namespace aiNS
{
	const int speed = 10;
}

class AI : public VertexShape {

	
public:

	
	std::map<CooldownType, float>	cooldown;
	GUIBar*							healthBar;
	ParticleSource					ps;

	AI() = default;
	~AI();

	AI(D3DXVECTOR3& pos, D3DXVECTOR3& dimension, D3DXVECTOR3& scale, D3DXVECTOR3& color);

	void init(Graphics*, Audio*);
	void draw(D3DXMATRIX&);
	void update(float, std::vector<VertexShape*>&);
	void move(std::vector<VertexShape*>& vS, float);
	void respawn(std::vector<VertexShape*>& vS);
	void die();
	void checkObstaclesCollision(std::vector<VertexShape*>& vS, bool x);
	void blink(std::vector<VertexShape*>&, float);
	void teleport(std::vector<VertexShape*>&, float);

	int randX(){ return randInt(-cameraNS::x + 2, cameraNS::x - 2); }
	int randY(){ return randInt(-cameraNS::y + 2, cameraNS::y - 2); }
};
