#include "Hide.h"

Hide::Hide()
{
}

Hide::~Hide()
{

}

void Hide::initialize(NodeManager* nM)
{
	Behaviour::initialize(nM);

	currentBehaviour = behaviourNS::HIDE;
	nextBehaviour = behaviourNS::HIDE;
	nodeManager->setTarget(nodeNS::OBJECT_TYPE_OBSTACLE);
	printf("HIDE\n");
}

void Hide::act(std::vector<VertexShape*>& vS, AI* computer)
{
	Node* end = nodeManager->getEnd();
	Node* start = nodeManager->getStart();

	if (bestMove != nullptr)
	{
		if (nodeManager->getStart() == bestMove)
			bestMove = nodeManager->determineBestNode();
	}
	else
		bestMove = nodeManager->determineBestNode();

	auto neighbours = end->getNeighbours();
	if (bestMove != nullptr)
	{
		double x = bestMove->pos.x - start->pos.x;
		double y = bestMove->pos.y - start->pos.y;

		computer->velocity.x = x;
		computer->velocity.y = y;

		if (nodeManager->heuristic(start, end) < behaviourNS::range)						// teleport when near the obstacle
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

			nodeManager->setTarget(nodeNS::OBJECT_TYPE_OBSTACLE);							// reset target
		}
	}
}

void Hide::randBehaviour()
{
	Node* end = nodeManager->getEnd();

	auto r = randInt(0, behaviourNS::behaviourNum * behaviourNS::baseRand);

	if (r < behaviourNS::baseRand * 2)
		nextBehaviour = behaviourNS::RUN;

	else if (r < behaviourNS::baseRand * 3.5)
		nextBehaviour = behaviourNS::TARGET_PLAYER;

	else if (r < behaviourNS::baseRand * 4)
		nextBehaviour = behaviourNS::STOP;
}
