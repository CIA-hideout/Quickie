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
			setShuffle(qEnvironmentObj);
			timer = 0;
		}
		
		// Run this if random mode is activated
		if (isRandomGen) {
			levelCount++;
			setRandom();
			timer = 0;
			printf("Me run something!");
		}
		timer = 0;
	}
}

// set obstacles location for level 1
void LevelManager::setLevelOne(std::vector<VertexShape*> vS)
{
	audio->stopCue(BGMRand);
	for (int i = 0; i < vS.size(); i++) {
		if (vS[i]->objectType == OBJECT_TYPE_OBSTACLE) {
			Obstacle* tempObs = (Obstacle*)vS[i];
			tempObs->setLevel1(levelCount);
		}
	}
	audio->playCue(BGMRand);
}

// set obstacles location for level 2
void LevelManager::setLevelTwo(std::vector<VertexShape*> vS)
{
	audio->stopCue(BGMRand);
	for (int i = 0; i < vS.size(); i++) {
		if (vS[i]->objectType == OBJECT_TYPE_OBSTACLE) {
			Obstacle* tempObs = (Obstacle*)vS[i];
			tempObs->setLevel2(levelCount);
		}
	}
	audio->playCue(BGMRand);

}

// set obstacles location for level 3
void LevelManager::setLevelThree(std::vector<VertexShape*> vS)
{
	audio->stopCue(BGMRand);
	for (int i = 0; i < vS.size(); i++) {
		if (vS[i]->objectType == OBJECT_TYPE_OBSTACLE) {
			Obstacle* tempObs = (Obstacle*)vS[i];
			tempObs->setLevel3(levelCount);
		}
	}
	audio->playCue(BGMRand);
}

// set obstacles location for the shuffled levels
void LevelManager::setShuffle(std::vector<VertexShape*> vS)
{
	// assign random levels into vector
	if (shuffleLevel.empty())
		shuffle();

	int level = shuffleLevel[0];
	shuffleLevel.erase(shuffleLevel.begin()); // clear 1st element 	   

	switch (level)
	{
		case 1: setLevelOne(vS);
				break;

		case 2: setLevelTwo(vS);
				break;

		case 3: setLevelThree(vS);
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

	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::shuffle(shuffleLevel.begin(), shuffleLevel.end(), rng); //ramdomise vector
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