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

	const UINT	sqr1X = GAME_WIDTH / 5;
	const UINT	sqr2X = GAME_WIDTH / 1.5;
	const UINT	sqrY = GAME_HEIGHT / 2.5;
	const int	z = 19.5;
	const int	speed = 10;
}

class EndScreen : public State
{

	Player* sqr1;
	Player* sqr2;
	D3DXVECTOR2					sqr1Pos = D3DXVECTOR2(endscreenNS::sqr1X, endscreenNS::sqrY);
	D3DXVECTOR2					sqr2Pos = D3DXVECTOR2(endscreenNS::sqr2X, endscreenNS::sqrY);
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
