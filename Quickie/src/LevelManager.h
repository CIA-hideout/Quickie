/* To manage the generation and moving of obstacles on 
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

	// Levels are just the playing fields
	void setLevelOne(std::vector<VertexShape*>);	// set Lvl 1
	void setLevelTwo(std::vector<VertexShape*>);	// set Lvl 2
	void setLevelThree(std::vector<VertexShape*>);	// set Lvl 3
	void setRandomLevel(std::vector<VertexShape*>);	// randomly set the levels


private:
	float timer;	
	int maxX = 15;		// max value for X coordinates
	int minX = -15;		// min value for X coordinates
	int maxY = 18;		// max value for Y coordinates
	int minY = -18;		// min value for Y coordinates
	double zAxis = 19.5;
};