#pragma once

#include <vector>
#include <stack>

#include "State.h"
#include "CollisionManager.h"
#include "Player.h"
#include "Wall.h"
#include "Obstacle.h"
#include "LevelManager.h"

namespace endscreenNS {
	enum Mode	{
		RETURN_MAIN,
		REVERT
	};

	const std::string		options[] = { "Return" };
	const int				optionsLength = 1;
}

class EndScreen : public State
{
	D3DXMATRIX					worldMatrix;
	int							winnerID;

public:
	EndScreen();
	virtual ~EndScreen();

	void initialize(Graphics* graphics, Input* input, Audio* audio, rapidjson::Document& doc) override;
	void update() override;
	void ai() override{}
	void render() override;
	void collisions() override{}
	void releaseAll() override{}
	void resetAll() override{}
	void setWinner(std::vector<VertexShape*>);			// get Winner of the game
};