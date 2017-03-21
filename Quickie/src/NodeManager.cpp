#include "NodeManager.h"

void NodeManager::initialize(Graphics* g)
{
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

	end = nullptr;
}

void NodeManager::update(std::vector<VertexShape*>& vS, Player* sqr1, AI* computer)
{
	obstacleNodes.clear();
	emptyNodes.clear();
	for (auto x = 0; x <nodesOnScreen.size(); ++x)
	{
		std::vector<Node>* pVect = &nodesOnScreen.at(x);

		for (auto y = 0; y < pVect->size(); ++y)
		{
			Node* temp = &pVect->at(y);
			temp->update(vS, sqr1, computer);

			if (temp->getCurrentObject() == nodeNS::OBJECT_TYPE_AI)
				start = temp;

			if (temp->getCurrentObject() == nodeNS::OBJECT_TYPE_PLAYER)
				player = temp;

			if (temp->getCurrentObject() == nodeNS::OBJECT_TYPE_OBSTACLE)
				obstacleNodes.push_back(temp);


			if (temp->getCurrentObject() == nodeNS::OBJECT_TYPE_NODE)
				emptyNodes.push_back(temp);

			temp->visible = false;
		}
	}

	if (end != nullptr)
		end->visible = true;
}

void NodeManager::draw(D3DXMATRIX worldMatrix)
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

Node* NodeManager::determineBestNode()
{
	if (start != nullptr && end != nullptr)
	{
		auto best = 0;
		auto neighbours = start->getNeighbours();

		//start->visible = true;
		for (auto i = 0; i < neighbours.size(); ++i)
		{
			auto neighbour = neighbours[i];

			if (neighbour->getCurrentObject() != nodeNS::OBJECT_TYPE_OBSTACLE)
			{
				if (previousNodes.size() > 0)
				{
					if (neighbour != previousNodes.top())
					{
						neighbour->h = heuristic(neighbour, end);

						if (neighbour->h <= neighbours[best]->h)
							best = i;
					}
				}
				else
				{
					neighbour->h = heuristic(neighbour, end);

					if (neighbour->h <= neighbours[best]->h)
						best = i;
				}
			}
		}

		neighbours[best]->visible = true;
		previousNodes.push(neighbours[best]);
		return neighbours[best];
	}

	return nullptr;
}

double NodeManager::heuristic(Node* initial, Node* target) const
{
	unsigned int x = target->i - initial->i;
	unsigned int y = target->j - initial->j;

	auto xy = x*x + y*y;
	return sqrt(xy);
}

void NodeManager::setTarget(nodeNS::ObjectType target)
{

	switch (target)
	{
	case nodeNS::OBJECT_TYPE_PLAYER:
		end = player;
		break;

	case nodeNS::OBJECT_TYPE_OBSTACLE:
		end = obstacleNodes.at(randInt(0, obstacleNodes.size() - 1));
		break;

	case nodeNS::OBJECT_TYPE_NODE:
		end = emptyNodes.at(randInt(0, emptyNodes.size() - 1));
		break;

	}

	previousNodes.empty(); // reset gscore
}