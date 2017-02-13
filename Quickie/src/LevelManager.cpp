#include "LevelManager.h"

LevelManager::LevelManager()
{
	
}

LevelManager::~LevelManager()
{
	
}

void LevelManager::init(Audio* a, std::vector<VertexShape*> vS, std::vector<VertexShape*> vP)
{
	audio = a;
	qEnvironmentObj = vS;
	qPlayers = vP;
}

void LevelManager::update(float deltaTime)
{
	timer += deltaTime;
	//printf("%.2f\n", timer);
	if (timer >= LEVEL_TIME) {
		// Run this if shuffled mode is activated
		if (isShuffled) {
			levelCount++;
			setShuffle();
			timer = 0;
		}
		
		// Run this if random mode is activated
		if (isRandomGen) {
			levelCount++;
			setRandom();
			timer = 0;
		}
		timer = 0;
	}
}

// set obstacles location for level 1
void LevelManager::setLevelOne()
{
	audio->stopCue(BGMRand);
	for (int i = 0; i < qEnvironmentObj.size(); i++) {
		if (qEnvironmentObj[i]->objectType == OBJECT_TYPE_OBSTACLE) {
			Obstacle* tempObs = (Obstacle*)qEnvironmentObj[i];
			tempObs->setLevel1(levelCount);
		}
	}
	audio->playCue(BGMRand);
}

// set obstacles location for level 2
void LevelManager::setLevelTwo()
{
	audio->stopCue(BGMRand);
	for (int i = 0; i < qEnvironmentObj.size(); i++) {
		if (qEnvironmentObj[i]->objectType == OBJECT_TYPE_OBSTACLE) {
			Obstacle* tempObs = (Obstacle*)qEnvironmentObj[i];
			tempObs->setLevel2(levelCount);
		}
	}
	audio->playCue(BGMRand);

}

// set obstacles location for level 3
void LevelManager::setLevelThree()
{
	audio->stopCue(BGMRand);
	for (int i = 0; i < qEnvironmentObj.size(); i++) {
		if (qEnvironmentObj[i]->objectType == OBJECT_TYPE_OBSTACLE) {
			Obstacle* tempObs = (Obstacle*)qEnvironmentObj[i];
			tempObs->setLevel3(levelCount);
		}
	}
	audio->playCue(BGMRand);
}

// set obstacles location for the shuffled levels
void LevelManager::setShuffle()
{
	// assign random levels into vector
	if (shuffleLevel.empty())
		shuffle();

	int level = shuffleLevel[0];
	shuffleLevel.erase(shuffleLevel.begin()); // clear 1st element 	   

	switch (level)
	{
		case 1: setLevelOne();
				break;

		case 2: setLevelTwo();
				break;

		case 3: setLevelThree();
				break;

		default: break;
	}
}

// shuffle the levels and store into vector
void LevelManager::shuffle()
{
	isShuffled = true;
	shuffleLevel.push_back(1);
	shuffleLevel.push_back(2);
	shuffleLevel.push_back(3);
	
	shuffleLevel = randIntVector(shuffleLevel);
}

// pure randomisation of obstacle location and size
void LevelManager::setRandom()
{
	isRandomGen = true;
	audio->stopCue(BGMRand);

	for (int i = 0; i < qEnvironmentObj.size(); i++) {
		if (qEnvironmentObj[i]->objectType == OBJECT_TYPE_OBSTACLE) {
			Obstacle* tempObs = (Obstacle*)qEnvironmentObj[i];
			tempObs->setRandom(levelCount, qEnvironmentObj, qPlayers);
		}
	}
	
	audio->playCue(BGMRand);
}