#pragma once

#include "ParticleSource.h"
#include "QLine.h"
#include "GUIBar.h"
#include "random.h"

enum CooldownType {
	COOLDOWN_BLINK,
	COOLDOWN_TELEPORT,
	INVULNERABLE,
	SPAWN_TIME
};

namespace playerNS
{
	const int length = 2;
	const int breadth = 2;
	const int height = 2;
	const int z = 29.5;

	const int	speed = 10;
}

class Player : public VertexShape {
public:

	std::map<CooldownType, float>	cooldown;
	std::map<Control, int>			controls;
	bool							controlled = false;
	bool							controlledTP = false;
	GUIBar*							healthBar;
	static int						winner;
	ParticleSource					ps;

	Player() = default;
	~Player();

	Player(D3DXVECTOR3& pos, D3DXVECTOR3& dimension, D3DXVECTOR3& scale, D3DXVECTOR3& color);

	void init(Graphics*, Input*, Audio*);
	void draw(D3DXMATRIX&);
	void update(float, std::vector<VertexShape*>&);
	void move(std::vector<VertexShape*>& vS, float);
	void respawn(std::vector<VertexShape*>& vS);
	void die();
	void checkObstaclesCollision(std::vector<VertexShape*>& vS, bool x);
	void blink(std::vector<VertexShape*>&, float);
	void teleport(std::vector<VertexShape*>&, float);
	void assignControl(rapidjson::Document&, int player);

	int randX(){ return randInt(-cameraNS::x + 2, cameraNS::x - 2); }
	int randY(){ return randInt(-cameraNS::y + 2, cameraNS::y - 2); }
};
