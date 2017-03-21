#pragma once

#include "VertexShape.h"
#include "AI.h"
#include "NodeManager.h"

namespace behaviourNS
{
	const int targetsNum = 3;
	const int behaviourNum = 4;
	const int behaviourRand = 1000;
	const int baseRand = 100;
	const int range = 3;

	enum Type
	{
		TARGET_PLAYER,
		RUN,
		HIDE,
		STOP
	};
}

class Behaviour
{

protected:
	NodeManager* nodeManager;
	behaviourNS::Type currentBehaviour;
	behaviourNS::Type nextBehaviour;
	static bool randomed;

public:

	Behaviour();
	virtual ~Behaviour();

	virtual void initialize(NodeManager* nM);
	virtual void act(std::vector<VertexShape*>& vS, AI* computer) = 0;
	virtual void randBehaviour() = 0;

	behaviourNS::Type getCurrentBehaviour() const { return currentBehaviour; }
	behaviourNS::Type getNextBehaviour() const { return nextBehaviour; }
	static bool getRandomed() { return randomed; }

	static void setRandomed(bool r) { randomed = r; }
};