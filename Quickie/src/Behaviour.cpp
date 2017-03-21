#include "Behaviour.h"

Behaviour::Behaviour()
{
	nodeManager = nullptr;
	currentBehaviour = behaviourNS::TARGET_PLAYER;
	nextBehaviour = behaviourNS::TARGET_PLAYER;
}

Behaviour::~Behaviour()
{
}

void Behaviour::initialize(NodeManager* nM)
{
	bestMove = nullptr;
	nodeManager = nM;
}


//void Behaviour::update(std::vector<VertexShape*>& vS, std::vector<Node*> obstacleNodes, std::vector<Node*> emptyNodes, AI &computer)
//{
//
//		if (timeGetTime() % behaviourNS::behaviourRand < behaviourNS::behaviourRand / 50)
//		{
//			randBehaviour(obstacleNodes, emptyNodes);
//		}
//
//		if (start == nullptr || end == nullptr)
//			randBehaviour(obstacleNodes, emptyNodes);
//		else
//			act(vS, computer);
//}
//
//void Behaviour::act(std::vector<VertexShape*>& vS, AI computer)
//{
//
//	Node* bestMove = determineNextMove();
//
//	auto neighbours = end->getNeighbours();
//	if (std::find(neighbours.begin(), neighbours.end(), start) == neighbours.end() && bestMove != nullptr)
//	{
//		double x = bestMove->pos.x - start->pos.x;
//		double y = bestMove->pos.y - start->pos.y;
//
//		if (currentBehaviour != aiNS::STOP)
//		{
//			computer.velocity.x = x;
//			computer.velocity.y = y;
//		}
//	}
//
//	switch (currentBehaviour)
//	{
//	case aiNS::TARGET_PLAYER:
//
//		// blink on a 25% chance
//
//		if (randInt(0, behaviourNS::baseRand) < 25)
//		{
//			if (heuristic(start, end) < behaviourNS::range)
//			{
//				if (computer.cooldown.at(COOLDOWN_BLINK) <= 0) {
//					if (computer.velocity.x != 0.0f || computer.velocity.y != 0.0f) {
//						float r_;
//						if (computer.velocity.x >= 0)
//							r_ = atan(computer.velocity.y / computer.velocity.x);
//						else if (computer.velocity.x < 0)
//							r_ = D3DX_PI + atan(computer.velocity.y / computer.velocity.x);
//						computer.blink(vS, r_);
//					}
//				}
//			}
//			else
//			{
//				currentBehaviour = aiNS::HIDE;
//			}
//		}
//
//		break;
//
//	case aiNS::HIDE:
//
//		// teleport on a 25% chance
//
//		if (randInt(0, behaviourNS::baseRand) < 25)
//		{
//			if (heuristic(start, end) < behaviourNS::range)
//			{
//				if (computer.velocity.x != 0.0f || computer.velocity.y != 0.0f) {
//					float r_;
//					if (computer.velocity.x >= 0)
//						r_ = atan(computer.velocity.y / computer.velocity.x);
//					else if (computer.velocity.x < 0)
//						r_ = D3DX_PI + atan(computer.velocity.y / computer.velocity.x);
//
//					computer.teleport(vS, r_);
//				}
//			}
//			else
//			{
//				currentBehaviour = aiNS::TARGET_PLAYER;
//			}
//		}
//		break;
//
//	case aiNS::RUN:
//
//		if (randInt(0, behaviourNS::baseRand) < 5)
//		{
//			currentBehaviour = aiNS::HIDE;
//		}
//		else if (randInt(0, behaviourNS::baseRand) < 10)
//		{
//			currentBehaviour = aiNS::STOP;
//		}
//
//		break;
//	}
//
//
//}
//
//void Behaviour::randBehaviour(std::vector<Node*> obstacleNodes, std::vector<Node*> emptyNodes)
//{
//	auto r = randInt(0, behaviourNS::behaviourNum * behaviourNS::baseRand);
//
//	if (r < behaviourNS::baseRand * 1.5)
//	{
//		currentBehaviour = aiNS::TARGET_PLAYER;
//		end = player;
//	}
//	else if (r < behaviourNS::baseRand * 3)
//	{
//		currentBehaviour = aiNS::RUN;
//		end = emptyNodes.at(randInt(0, emptyNodes.size() - 1));
//	}
//	else if (r < behaviourNS::baseRand * 3.5)
//	{
//		currentBehaviour = aiNS::HIDE;
//		end = obstacleNodes.at(randInt(0, obstacleNodes.size() - 1));
//	}
//	else if (r < behaviourNS::baseRand * 4)
//	{
//		currentBehaviour = aiNS::STOP;
//	}
//}


//void Behaviour::modifiedRandBehaviour(float modifier, aiNS::Behaviour selector)
//{
//	auto r = randInt(0, behaviourNS::behaviourNum * (behaviourNS::baseRand - 1) + (behaviourNS::baseRand * modifier));
//
//	for (auto i = 1; i <= behaviourNS::behaviourNum; ++i)
//	{
//
//		if (i == selector)
//		{
//			if (r > behaviourNS::baseRand * (i - 1) && r < behaviourNS::baseRand * i * modifier)
//			{
//				currentBehaviour = aiNS::Behaviour(i - 1);
//				if (i < behaviourNS::targetsNum)
//					setTarget(nodeNS::ObjectType(i - 1));
//			}
//		}
//		else
//		{
//			if (r > behaviourNS::baseRand * (i - 1) && r < behaviourNS::baseRand * i)
//			{
//				currentBehaviour = aiNS::Behaviour(i - 1);
//				if (i < behaviourNS::targetsNum)
//					setTarget(nodeNS::ObjectType(i - 1));
//			}
//		}
//	}
//}