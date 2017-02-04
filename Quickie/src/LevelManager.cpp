#include "LevelManager.h"

LevelManager::LevelManager()
{

}

LevelManager::~LevelManager()
{

}

// set obstacles location for level 1
void LevelManager::setLevelOne(std::vector<VertexShape*> vS)
{
	for (int i = 0; i < vS.size(); i++) {
		Obstacle* tempObs = (Obstacle*) vS[i];
		tempObs->setLevel1();
	}
}

// set obstacles location for level 2
void LevelManager::setLevelTwo(std::vector<VertexShape*> vS)
{
	for (int i = 0; i < vS.size(); i++) {
		Obstacle* tempObs = (Obstacle*)vS[i];
		tempObs->setLevel2();
	}
}


// set obstacles location for level 3
void LevelManager::setLevelThree(std::vector<VertexShape*> vS)
{
	for (int i = 0; i < vS.size(); i++) {
		Obstacle* tempObs = (Obstacle*)vS[i];
		tempObs->setLevel3();
	}
}