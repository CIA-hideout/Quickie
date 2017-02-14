#include "Behaviour.h"

Behaviour::Behaviour()
{
	start = nullptr;
	end = nullptr;
	graphics = nullptr;
}

Behaviour::~Behaviour()
{
}

void Behaviour::initialize(Graphics* g, AI* a)
{
	graphics = g;
	computer = a;
	currentBehaviour = behaviourNS::STOP;

	auto i = 0, j = 0;
	for (int x = -cameraNS::x; x <= cameraNS::x; x += 2)
	{
		std::vector<Node> tempVector = std::vector<Node>();

		for (int y = cameraNS::y; y >= -cameraNS::y; y -= 4)
		{
			Node temp = Node(D3DXVECTOR3(x, y, playerNS::z), D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), COLOR_RED);
			temp.init(g);
			temp.i = i;
			temp.j = j;
			tempVector.push_back(temp);
			j++;
		}
		nodesOnScreen.push_back(tempVector);
		j = 0;
		i++;
	}
	for (auto x = 0; x < nodesOnScreen.size(); ++x)
	{
		std::vector<Node>* pVect = &nodesOnScreen.at(x);

		for (auto y = 0; y < pVect->size(); ++y)
		{
			Node* temp = &pVect->at(y);
			temp->setNeighbours(&nodesOnScreen);
		}
	}
}

void Behaviour::update(std::vector<VertexShape*>& vS, Player* target)
{
	obstacleNodes.clear();
	emptyNodes.clear();
	for (auto x = 0; x <nodesOnScreen.size(); ++x)
	{
		std::vector<Node>* pVect = &nodesOnScreen.at(x);

		for (auto y = 0; y < pVect->size(); ++y)
		{
			Node* temp = &pVect->at(y);
			temp->update(vS, target, computer);

			if (temp->getCurrentObject() == nodeNS::OBJECT_TYPE_AI)		// set Behaviour as start
				start = temp;

			if (temp->getCurrentObject() == nodeNS::OBJECT_TYPE_PLAYER)
				player = temp;

			if (temp->getCurrentObject() == nodeNS::OBJECT_TYPE_OBSTACLE)
				obstacleNodes.push_back(temp);


			if (temp->getCurrentObject() == nodeNS::OBJECT_TYPE_NODE)
				emptyNodes.push_back(temp);
		}
	}
		
	if (obstacleNodes.size() != 0 && emptyNodes.size() != 0 && computer->cooldown.at(INVULNERABLE) < 0.0f && computer->alive)
	{
		if (timeGetTime() % behaviourNS::behaviourRand < behaviourNS::behaviourRand / 50)
		{
			randBehaviour();
		}

		if (start == nullptr || end == nullptr)
			randBehaviour();
		else
			act(vS);
	}
}

void Behaviour::setTarget(nodeNS::ObjectType target)
{

	switch (target)
	{
	case nodeNS::OBJECT_TYPE_PLAYER:
			end = player;
		break;

	case nodeNS::OBJECT_TYPE_OBSTACLE:
			end = obstacleNodes.at(randInt(0, obstacleNodes.size()));
		break;

	case nodeNS::OBJECT_TYPE_NODE:
			end = emptyNodes.at(randInt(0, emptyNodes.size()));
		break;

	}
}

void Behaviour::checkObstacles()
{
	obstacleNodes.clear();
	emptyNodes.clear();

	for (auto x = 0; x <nodesOnScreen.size(); ++x)
	{
		std::vector<Node>* pVect = &nodesOnScreen.at(x);

		for (auto y = 0; y < pVect->size(); ++y)
		{
			Node* temp = &pVect->at(y);

			if (temp->getCurrentObject() == nodeNS::OBJECT_TYPE_OBSTACLE)
				obstacleNodes.push_back(temp);


			if (temp->getCurrentObject() == nodeNS::OBJECT_TYPE_NODE)
				emptyNodes.push_back(temp);
		}
	}
}

void Behaviour::draw(D3DXMATRIX& worldMatrix)
{
	for (auto x = 0; x <nodesOnScreen.size(); ++x)
	{
		std::vector<Node>* pVect = &nodesOnScreen.at(x);

		for (auto y = 0; y < pVect->size(); ++y)
		{
			Node* temp = &pVect->at(y);
			temp->draw(worldMatrix);
		}
	}
}

Node* Behaviour::determineNextMove()
{
	if (start != nullptr && end != nullptr)
	{

		auto best = 0;
		auto neighbours = start->getNeighbours();
		for (auto i = 0; i < neighbours.size(); ++i)
		{
			auto neighbour = neighbours[i];

			if (neighbour->getCurrentObject() != nodeNS::OBJECT_TYPE_OBSTACLE)
			{
					neighbour->h = heuristic(neighbour, end);

					if (neighbours[i]->h <= neighbours[best]->h)
						best = i;
			}
		}
		return neighbours[best];
	}

	return nullptr;
}

double Behaviour::heuristic(Node* initial, Node* target) const
{
	unsigned int x = target->i - initial->i;
	unsigned int y = target->j - initial->j;

	auto xy = x*x + y*y;
	return sqrt(xy);
}

void Behaviour::act(std::vector<VertexShape*>& vS)
{

	Node* bestMove = determineNextMove();

	auto neighbours = end->getNeighbours();
	if (std::find(neighbours.begin(), neighbours.end(), start) == neighbours.end() && bestMove != nullptr)
	{
		double x = bestMove->pos.x - start->pos.x;
		double y = bestMove->pos.y - start->pos.y;

		if (currentBehaviour != behaviourNS::STOP)
		{
			computer->velocity.x = x;
			computer->velocity.y = y;
		}
	}

	switch (currentBehaviour)
	{
	case behaviourNS::TARGET_PLAYER:

		// blink on a 25% chance

		if (randInt(0, behaviourNS::baseRand) < 25)
		{
			if (heuristic(start, end) < behaviourNS::range)
			{
				if (computer->cooldown.at(COOLDOWN_BLINK) <= 0) {
					if (computer->velocity.x != 0.0f || computer->velocity.y != 0.0f) {
						float r_;
						if (computer->velocity.x >= 0)
							r_ = atan(computer->velocity.y / computer->velocity.x);
						else if (computer->velocity.x < 0)
							r_ = D3DX_PI + atan(computer->velocity.y / computer->velocity.x);
						computer->blink(vS, r_);
					}
				}
			}
			else
			{
				currentBehaviour = behaviourNS::HIDE;
			}
		}

		break;

	case behaviourNS::HIDE:

		// teleport on a 25% chance

		if (randInt(0, behaviourNS::baseRand) < 25)
		{
			if (heuristic(start, end) < behaviourNS::range)
			{
				if (computer->velocity.x != 0.0f || computer->velocity.y != 0.0f) {
					float r_;
					if (computer->velocity.x >= 0)
						r_ = atan(computer->velocity.y / computer->velocity.x);
					else if (computer->velocity.x < 0)
						r_ = D3DX_PI + atan(computer->velocity.y / computer->velocity.x);

					computer->teleport(vS, r_);
				}
			}
			else
			{
				currentBehaviour = behaviourNS::TARGET_PLAYER;
			}
		}
		break;

	case behaviourNS::RUN:

		if (randInt(0, behaviourNS::baseRand) < 5)
		{
			currentBehaviour = behaviourNS::HIDE;
		}
		else if (randInt(0, behaviourNS::baseRand) < 10)
		{
			currentBehaviour = behaviourNS::STOP;
		}

		break;
	}


}

void Behaviour::randBehaviour()
{
	auto r = randInt(0, behaviourNS::behaviourNum * behaviourNS::baseRand);

	if (r < behaviourNS::baseRand * 1.5)
	{
		currentBehaviour = behaviourNS::TARGET_PLAYER;
		end = player;
	}
	else if (r < behaviourNS::baseRand * 3)
	{
		currentBehaviour = behaviourNS::RUN;
		end = emptyNodes.at(randInt(0, emptyNodes.size() - 1));
	}
	else if (r < behaviourNS::baseRand * 3.5)
	{
		currentBehaviour = behaviourNS::HIDE;
		end = obstacleNodes.at(randInt(0, obstacleNodes.size() - 1));
	}
	else if (r < behaviourNS::baseRand * 4)
	{
		currentBehaviour = behaviourNS::STOP;
	}
}


//void Behaviour::modifiedRandBehaviour(float modifier, behaviourNS::Type selector)
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
//				currentBehaviour = behaviourNS::Type(i - 1);
//				if (i < behaviourNS::targetsNum)
//					setTarget(nodeNS::ObjectType(i - 1));
//			}
//		}
//		else
//		{
//			if (r > behaviourNS::baseRand * (i - 1) && r < behaviourNS::baseRand * i)
//			{
//				currentBehaviour = behaviourNS::Type(i - 1);
//				if (i < behaviourNS::targetsNum)
//					setTarget(nodeNS::ObjectType(i - 1));
//			}
//		}
//	}
//}