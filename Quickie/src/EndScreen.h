#pragma once

#include <vector>
#include <stack>

#include "State.h"
#include "CollisionManager.h"
#include "Player.h"
#include "Wall.h"
#include "Obstacle.h"
#include "LevelManager.h"

class EndScreen : public State
{
	D3DXMATRIX					worldMatrix;
	float*						deltaTime;

public:
	EndScreen();
	virtual ~EndScreen();

	void initialize(Graphics* graphics, Input* input, Audio* audio, rapidjson::Document& doc, float* deltaTime);
	void update() override;
	void ai() override{}
	void render() override;
	void collisions() override{}
	void releaseAll() override{}
	void resetAll() override{}
};