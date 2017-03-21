#include "TargetPlayer.h"

TargetPlayer::TargetPlayer()
{
}

TargetPlayer::~TargetPlayer()
{
	
}

void TargetPlayer::initialize(NodeManager* nM)
{
	Behaviour::initialize(nM);

	currentBehaviour = behaviourNS::TARGET_PLAYER;
	nextBehaviour = behaviourNS::TARGET_PLAYER;
	nodeManager->setTarget(nodeNS::OBJECT_TYPE_PLAYER);
	printf("TARGET\n");
}

void TargetPlayer::act(std::vector<VertexShape*>& vS, AI* computer)
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
	
	nodeManager->setTarget(nodeNS::OBJECT_TYPE_PLAYER);

	auto neighbours = end->getNeighbours();
	if (std::find(neighbours.begin(), neighbours.end(), start) == neighbours.end() && bestMove != nullptr)			// if end's neighbours has start, change behaviour
	{
		double x = bestMove->pos.x - start->pos.x;
		double y = bestMove->pos.y - start->pos.y;

		computer->velocity.x = x;
		computer->velocity.y = y;

		// blink, run or hide when near the player
		if (nodeManager->heuristic(start, end) < behaviourNS::range)
		{
			auto r = randInt(0, behaviourNS::baseRand);

			if (r < 50)				// blink 50% chance
			{
				if (computer->cooldown.at(COOLDOWN_BLINK) <= 0)
				{
					if (computer->velocity.x != 0.0f || computer->velocity.y != 0.0f)
					{
						float r_;
						if (computer->velocity.x >= 0)
							r_ = atan(computer->velocity.y / computer->velocity.x);
						else if (computer->velocity.x < 0)
							r_ = D3DX_PI + atan(computer->velocity.y / computer->velocity.x);
						computer->blink(vS, r_);
					}
				}
			}
			else if (r < 75)
			{
				nextBehaviour = behaviourNS::RUN;					// run 25% chance
			}
			else
			{
				nextBehaviour = behaviourNS::HIDE;					// hide 25% chance
			}
		}
	}
}

void TargetPlayer::randBehaviour()
{
	Node* end = nodeManager->getEnd();

	auto r = randInt(0, behaviourNS::behaviourNum * behaviourNS::baseRand);
		
	if (r < behaviourNS::baseRand * 2)
		nextBehaviour = behaviourNS::RUN;

	else if (r < behaviourNS::baseRand * 3.5)
		nextBehaviour = behaviourNS::HIDE;

	else if (r < behaviourNS::baseRand * 4)
		nextBehaviour = behaviourNS::STOP;
}
