/* To manage the location of the obstacles in each levels
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
#include "Audio.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

class LevelManager {
public:

	std::vector<VertexShape*> entityPool;

	LevelManager();
	~LevelManager();

	void init(Audio*);

	void update(float, std::vector<VertexShape*>, std::vector<VertexShape*>);

	// Set Different Levels during the Gameplay
	void setLevelOne(std::vector<VertexShape*>);		// set Lvl 1
	void setLevelTwo(std::vector<VertexShape*>);		// set Lvl 2
	void setLevelThree(std::vector<VertexShape*>);		// set Lvl 3
	void setShuffle(std::vector<VertexShape*>);			// set the shuffled levels
	void shuffle();										// shuffle the exisiting levels
	void setRandom(std::vector<VertexShape*>, std::vector<VertexShape*>);			// set the obstales location really randomly

	// setters
	void setShuffledBool(boolean newCon)	{ isShuffled = newCon; }
	void setRandomBool(boolean newCon)		{ isRandomGen = newCon; }

private:
	float timer = 0;
	int levelCount = 0;
	double zAxis = 29.5;
	boolean isShuffled = false;
	boolean isRandomGen = false;

	Audio* audio;		// Pointer to audio system

	std::vector<int> shuffleLevel;	// store the shuffled levels
};