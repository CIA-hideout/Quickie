#include "random.h"
#include "constants.h"
#include "Player.h"

std::random_device rd;     // only used once to initialise (seed) engine
std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)

bool randBool() {
	std::uniform_int_distribution<int> distribution(0, 1);
	return distribution(rng) == 0 ? true : false;
}

int randInt(int start, int end) {
	std::uniform_int_distribution<int> distribution(start, end);
	return distribution(rng);
}