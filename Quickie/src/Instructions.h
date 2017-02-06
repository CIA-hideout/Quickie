#pragma once

#include <vector>
#include "State.h"
#include "CollisionManager.h"
#include "Player.h"

class Instructions : public State
{
	bool			blink = false;
	D3DXMATRIX		worldMatrix;

	Player* sqr1 = new Player(D3DXVECTOR3(0, 0, 20 - 1), D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(255, 255, 255));
	Player* sqr2 = new Player(D3DXVECTOR3(10, 10, 20 - 1), D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 240, 240));

public:
	Instructions();
	virtual ~Instructions();

	void initialize(Graphics* graphics, Input* input) override;
	void update() override;
	void ai() override{};
	void render() override;
	void collisions() override{};
	void releaseAll() override{};
	void resetAll() override{};
};
