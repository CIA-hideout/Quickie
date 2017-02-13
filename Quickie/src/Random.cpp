#include "random.h"
#include "constants.h"
#include "Player.h"

std::random_device rd;     // only used once to initialise (seed) engine
std::mt19937 rng(rd());		// random-number engine used (Mersenne-Twister in this case)

bool randBool() {
	std::uniform_int_distribution<int> distribution(0, 1);
	return distribution(rng) == 0 ? true : false;
}

int randInt(int start, int end) {
	std::uniform_int_distribution<int> distribution(start, end);
	return distribution(rng);
}

float randFloat(float min, float max) {
	std::uniform_real_distribution<float> distribution(min, max);	
	return distribution(rng);
}

std::vector<D3DXVECTOR3> rand3DVector(std::vector<D3DXVECTOR3> vector) {
	std::shuffle(vector.begin(), vector.end(), rng);
	return vector;
}

std::vector<int> randIntVector(std::vector<int> vector){
	std::shuffle(vector.begin(), vector.end(), rng);
	return vector;
}