#pragma once

#include "State.h"
#include "CollisionManager.h"
#include "Player.h"
#include "LevelManager.h"

namespace menuNS
{
	enum Scene
	{
		BLINK,
		BLINK_OPPOSITE
	};

	const UINT	sqr1X = GAME_WIDTH / 5;
	const UINT	sqr2X = GAME_WIDTH / 1.5;
	const UINT	sqrY = GAME_HEIGHT / 4;
	const int	z = 19.5;
	const int	speed = 10;
}

class Menu : public State
{
	Player* sqr1;
	Player* sqr2;
	D3DXVECTOR2					sqr1Pos = D3DXVECTOR2(menuNS::sqr1X, menuNS::sqrY);
	D3DXVECTOR2					sqr2Pos = D3DXVECTOR2(menuNS::sqr2X, menuNS::sqrY);
	std::vector<VertexShape*>	qEnvironmentObj;
	menuNS::Scene				currentScene;

public:
	Menu();
	virtual ~Menu();
	bool canPlaySound = true;

	void initialize(Graphics* graphics, Input* input, Audio* audio, rapidjson::Document& doc, float* deltaTime) override;
	void update() override;
	void ai() override{};
	void render() override;
	void collisions() override{};
	void releaseAll() override{};
	void resetAll() override{};
};
