#pragma once

#include <vector>
#include "State.h"
#include "CollisionManager.h"
#include "Player.h"
#include "Wall.h"
#include "Obstacle.h"
#include "LevelManager.h"

class Gameplay : public State
{
	D3DXMATRIX					worldMatrix;
	rapidjson::Document			obstacleDoc;
	std::vector<VertexShape*>	qEnvironmentObj;
	std::vector<VertexShape*>	qPlayer;

	float*						deltaTime;
	LevelManager*				lManager;

	Obstacle* o1;
	Obstacle* o2;
	Obstacle* o3;
	Obstacle* o4;
	Obstacle* o5;
	Obstacle* o6;

	Wall* w1;		// - up
	Wall* w2; 		// - down
	Wall* w3; 		// | left
	Wall* w4;		// | right

	Player* sqr1;
	Player* sqr2;

public:
	Gameplay();
	virtual ~Gameplay();

	void initialize(Graphics* graphics, Input* input, Audio* audio, rapidjson::Document& doc, float* deltaTime);
	void update() override;
	void ai() override{};
	void render() override;
	void collisions() override{};
	void releaseAll() override{};
	void resetAll() override{};
};
