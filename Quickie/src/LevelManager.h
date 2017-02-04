/* To manage the generation and moving of obstacles for each level
 * 
 */

#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <random>

#include "VertexShape.h"
#include "Player.h"
#include "Obstacle.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

class LevelManager {
public:

	std::vector<VertexShape*> entityPool;

	LevelManager();
	~LevelManager();

	// To store location of obs
	void storeLvlOnePos();

	// Set Different Levels during the Gameplay
	void setLevelOne(std::vector<VertexShape*>);		// set Lvl 1
	void setLevelTwo(std::vector<VertexShape*>);		// set Lvl 2
	void setLevelThree(std::vector<VertexShape*>);	// set Lvl 3
	void setRandomLevel(std::vector<VertexShape*>);	// randomly set the levels
	

private:
	float timer = 0;
	int maxX = 15;		// max value for X coordinates
	int minX = -15;		// min value for X coordinates
	int maxY = 18;		// max value for Y coordinates
	int minY = -18;		// min value for Y coordinates
	double zAxis = 19.5;

	std::vector<D3DXVECTOR3> lvlOnePos;
	std::vector<D3DXVECTOR3> lvlTwoPos;
	std::vector<D3DXVECTOR3> lvlThreePos;

	std::vector<D3DXVECTOR3> lvlOneDimension;
};