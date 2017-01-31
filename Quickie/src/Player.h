#pragma once

#include "VertexShape.h"
#include "CollisionManager.h"

enum CooldownType {
	COOLDOWN_BLINK,
	COOLDOWN_TELEPORT
};

enum Control {
	CONTROL_UP,
	CONTROL_DOWN,
	CONTROL_LEFT,
	CONTROL_RIGHT,
	CONTROL_BL,
	CONTROL_TP
};

class Player : public VertexShape {
public:

	std::map<CooldownType, float>	cooldown;
	std::map<Control, int>			controls;
	int								playerId;

	Player() = default;
	~Player();

	Player(D3DXVECTOR3& pos, D3DXVECTOR3& dimension, D3DXVECTOR3& scale, D3DXVECTOR3& color);

	void init(Game*);
	void draw(D3DXMATRIX&);
	void update(float, std::vector<VertexShape*>&);
	void moveX(float&);
	void moveY(float&);
	void moveZ(float&);
	void move(std::vector<VertexShape*>& vS, float);
	void respawn();
	void blink(std::vector<VertexShape*>&);
	void teleport();
	void assignControl(rapidjson::Document&);

};
