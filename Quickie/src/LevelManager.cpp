#include "LevelManager.h"

LevelManager::LevelManager()
{
	storeLvlOnePos();
}

LevelManager::~LevelManager()
{

}

// To store the position of all obstacles in lvl 1
void LevelManager::storeLvlOnePos()
{
	lvlOnePos.push_back(LVL_ONE_OBS_1);
	lvlOnePos.push_back(LVL_ONE_OBS_2);
	lvlOnePos.push_back(LVL_ONE_OBS_3);
	lvlOnePos.push_back(LVL_ONE_OBS_4);
	lvlOnePos.push_back(LVL_ONE_OBS_5);
	lvlOnePos.push_back(LVL_ONE_OBS_6);

	lvlOneDimension.push_back(DIMENSION_HORIZONTAL_MEDIUM);
	lvlOneDimension.push_back(DIMENSION_VERTICAL_MEDIUM);
	lvlOneDimension.push_back(DIMENSION_HORIZONTAL_MEDIUM);
	lvlOneDimension.push_back(DIMENSION_VERTICAL_MEDIUM);
	lvlOneDimension.push_back(DIMENSION_HORIZONTAL_LARGE);
	lvlOneDimension.push_back(DIMENSION_HORIZONTAL_LARGE);
}

// set obstacles location for level 1
void LevelManager::setLevelOne(std::vector<VertexShape*> vS)
{
	for (int i = 0; i < vS.size(); i++) {
		Obstacle* tempObs = (Obstacle*) vS[i];

		tempObs->setPosition(lvlOnePos[i]);
		tempObs->setDimension(lvlOneDimension[i]);
	}
}