#pragma once

#include "Obstacle.h"
#include <algorithm>
#include <random>


class Wall : public Obstacle {

public:
	Wall() = default;

	Wall(D3DXVECTOR3& pos, D3DXVECTOR3& dimension, D3DXVECTOR3& scale, D3DXVECTOR3& color);
	
	~Wall();

};