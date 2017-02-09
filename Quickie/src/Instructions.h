#pragma once

#include <vector>
#include "State.h"
#include "CollisionManager.h"
#include "Player.h"
#include <stack>

namespace instructionsNS
{
	enum Scene
	{
		MOVE_RIGHT,
		MOVE_LEFT,
		MOVE_UP,
		MOVE_DOWN,
		TELEPORT,
		BLINK,
		RESPAWN
	};
}

class Instructions : public State
{
	instructionsNS::Scene					currentScene;

	Player* sqr1;
	Player* sqr2;
	D3DXVECTOR2		sqr1Pos = D3DXVECTOR2(stateNS::sqr1X, stateNS::sqrY);
	D3DXVECTOR2		sqr2Pos = D3DXVECTOR2(stateNS::sqr2X, stateNS::sqrY);
	std::vector<VertexShape*>	qEnvironmentObj;

public:
	Instructions();
	virtual ~Instructions();

	void initialize(Graphics* graphics, Input* input, Audio* audio, rapidjson::Document& doc, float* deltaTime) override;
	void update() override;
	void ai() override{};
	void render() override;
	void collisions() override{};
	void releaseAll() override{};
	void resetAll() override{};
};
