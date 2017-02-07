#pragma once

#include "ParticleSource.h"
#include "QLine.h"
#include "GUIBar.h"

enum CooldownType {
	COOLDOWN_BLINK,
	COOLDOWN_TELEPORT,
	INVULNERABLE,
	SPAWN_TIME
};

class Player : public VertexShape {
public:

	std::map<CooldownType, float>	cooldown;
	std::map<Control, int>			controls;
	bool							locked;
	GUIBar*							healthBar;

	ParticleSource					ps;

	Player() = default;
	~Player();

	Player(D3DXVECTOR3& pos, D3DXVECTOR3& dimension, D3DXVECTOR3& scale, D3DXVECTOR3& color);

	void init(Graphics*, Input*);
	void draw(D3DXMATRIX&);
	void update(float, std::vector<VertexShape*>&);
	void move(std::vector<VertexShape*>& vS, float);
	void respawn();
	void blink(std::vector<VertexShape*>&, float);
	void teleport(std::vector<VertexShape*>&, float);
	void assignControl(rapidjson::Document&, int player);
	
	bool getLocked(){ return locked; }
	void setLocked(bool l){ locked = l; }

};
