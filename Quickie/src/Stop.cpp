#include "Stop.h"

Stop::Stop()
{
}

Stop::~Stop()
{

}

void Stop::initialize(NodeManager* nM)
{
	Behaviour::initialize(nM);

	currentBehaviour = behaviourNS::STOP;
	nextBehaviour = behaviourNS::STOP;
	nodeManager->setTarget(nodeNS::OBJECT_TYPE_PLAYER);
	printf("STOP\n");
}

void Stop::act(std::vector<VertexShape*>& vS, AI* computer)
{
	Node* end = nodeManager->getEnd();
	Node* start = nodeManager->getStart();

	if (nodeManager->heuristic(start, end) < behaviourNS::range && !randomed)						// run or teleport and target player when near the obstacle
	{
		auto r = randInt(0, behaviourNS::baseRand);

		if (r < 75)					// run 75% chance
		{
			nextBehaviour = behaviourNS::RUN;
		}
		else						// teleport and target player 25% chance
		{
			if (computer->velocity.x != 0.0f || computer->velocity.y != 0.0f)
			{
				float r_;
				if (computer->velocity.x >= 0)
					r_ = atan(computer->velocity.y / computer->velocity.x);
				else if (computer->velocity.x < 0)
					r_ = D3DX_PI + atan(computer->velocity.y / computer->velocity.x);

				computer->teleport(vS, r_);
			}

			nextBehaviour = behaviourNS::TARGET_PLAYER;
		}

		randomed = true;
	}
}

void Stop::randBehaviour()
{
	Node* end = nodeManager->getEnd();

	auto r = randInt(0, behaviourNS::behaviourNum * behaviourNS::baseRand);

	if (r < behaviourNS::baseRand * 2)
		nextBehaviour = behaviourNS::RUN;

	else if (r < behaviourNS::baseRand * 3.5)
		nextBehaviour = behaviourNS::HIDE;

	else if (r < behaviourNS::baseRand * 4)
		nextBehaviour = behaviourNS::TARGET_PLAYER;
}
