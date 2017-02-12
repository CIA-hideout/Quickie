#pragma once

#include "ParticleSource.h"
#include "QLine.h"
#include "GUIBar.h"
#include "random.h"

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

	int randX_2D(){ return randInt(1, GAME_WIDTH - 1); }
	int randY_2D(){ return randInt(1, GAME_HEIGHT - 1); }
};
