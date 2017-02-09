#pragma once

#include <vector>
#include "State.h"
#include "CollisionManager.h"
#include "Player.h"
#include "LevelManager.h"
#include "Menu.h"

namespace endscreenNS
{
	enum Scene
	{
		EXPLODE,
		RESPAWN
	};
}

class EndScreen : public State
{

	Player* sqr1;
	Player* sqr2;
	D3DXVECTOR2					sqr1Pos = D3DXVECTOR2(stateNS::sqr1X, stateNS::sqrY);
	D3DXVECTOR2					sqr2Pos = D3DXVECTOR2(stateNS::sqr2X, stateNS::sqrY);
	std::vector<VertexShape*>	qEnvironmentObj;
	endscreenNS::Scene			currentScene;

public:
	EndScreen();
	virtual ~EndScreen();
	Menu* menu;

	void initialize(Graphics* graphics, Input* input, Audio* audio, rapidjson::Document& doc, float* deltaTime) override;
	void update() override;
	void ai() override{}
	void render() override;
	void collisions() override{}
	void releaseAll() override{}
	void resetAll() override{}
};
