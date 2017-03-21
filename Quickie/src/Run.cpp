#include "Run.h"

Run::Run()
{
}

Run::~Run()
{

}

void Run::initialize(NodeManager* nM)
{
	Behaviour::initialize(nM);

	currentBehaviour = behaviourNS::RUN;
	nextBehaviour = behaviourNS::RUN;
	nodeManager->setTarget(nodeNS::OBJECT_TYPE_NODE);
	printf("RUN\n");
}

void Run::act(std::vector<VertexShape*>& vS, AI* computer)
{
	Node* bestMove = nodeManager->determineBestNode();
	Node* end = nodeManager->getEnd();
	Node* start = nodeManager->getStart();


	auto neighbours = end->getNeighbours();
	if (std::find(neighbours.begin(), neighbours.end(), start) == neighbours.end() && bestMove != nullptr)			// if end's neighbours has start, change behaviour
	{
		double x = bestMove->pos.x - start->pos.x;
		double y = bestMove->pos.y - start->pos.y;

		computer->velocity.x = x;
		computer->velocity.y = y;

		for (auto i = 0; i < neighbours.size(); i++)			// target player or stop moving when near an obstacle
		{
			if (neighbours[i]->getCurrentObject() == nodeNS::OBJECT_TYPE_OBSTACLE && !randomed)
			{
				auto r = randInt(0, behaviourNS::baseRand);

				if (r < 75)		// target player 75% chance
					nextBehaviour = behaviourNS::TARGET_PLAYER;
				else			// stop moving 25% chance
					nextBehaviour = behaviourNS::STOP;

				randomed = true;
			}
		}
	}
	else if (!randomed)
	{
		randBehaviour();

		randomed = true;
	}
}

void Run::randBehaviour()
{
	Node* end = nodeManager->getEnd();

	auto r = randInt(0, behaviourNS::behaviourNum * behaviourNS::baseRand);

	if (r < behaviourNS::baseRand * 3)
		nextBehaviour = behaviourNS::TARGET_PLAYER;

	else if (r < behaviourNS::baseRand * 3.5)
		nextBehaviour = behaviourNS::HIDE;

	else if (r < behaviourNS::baseRand * 4)
		nextBehaviour = behaviourNS::STOP;
}
