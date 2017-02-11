#include "PathFinder.h"

PathFinder::PathFinder()
{
}

PathFinder::~PathFinder()
{
}

void PathFinder::initialize(Graphics* g)
{
	graphics = g;

	auto i = 0, j = 0;

	for (int x = -cameraNS::x; x <= cameraNS::x; ++x)
	{
		std::vector<Node> tempVector = std::vector<Node>();
		
		for (int y = -cameraNS::y; y <= cameraNS::y; ++y)
		{
			Node temp = Node(D3DXVECTOR3(x, y, playerNS::z), D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(240, 240, 0));
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

void PathFinder::update(std::vector<VertexShape*>& vS, Player* p)
{
	for (auto x = 0; x <nodesOnScreen.size(); ++x)
	{
		std::vector<Node>* pVect = &nodesOnScreen.at(x);

		for (auto y = 0; y < pVect->size(); ++y)
		{
			Node* temp = &pVect->at(y);
			temp->update(vS, p);

			if (temp->objectType == OBJECT_TYPE_AI)
				start = temp;
		}
	}

	determinePath();
}

void PathFinder::setTargetNode(Node* target)
{
	for (auto x = 0; x <nodesOnScreen.size(); ++x)
	{
		std::vector<Node>* pVect = &nodesOnScreen.at(x);

		for (auto y = 0; y < pVect->size(); ++y)
		{
			Node* temp = &pVect->at(y);
			
			if (temp == target)
			{
				end = target;
				break;
			}
		}
	}
}

void PathFinder::draw(D3DXMATRIX& worldMatrix)
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

bool PathFinder::determinePath()
{
	openSet.push_back(start);

	while (openSet.size() > 0)
	{
		auto best = 0;

		for (auto i = 0; i < openSet.size(); ++i)
		{
			if (openSet[i]->f < openSet[best]->f)
			{
				best = i;
			}
		}

		auto current = openSet[best];

		if (current == end)
		{
			path.clear();

			auto temp = current;
			path.push_back(temp);

			while (temp->getprevious() != nullptr)
			{
				path.push_back(temp->getprevious());
				temp = temp->getprevious();
			}

			return true;
		}

		openSet.erase(std::remove(openSet.begin(), openSet.end(), openSet[best]), openSet.end());
		closedSet.push_back(current);

		auto neighbours = current->getNeighbours();
		for (auto i = 0; i < neighbours.size(); ++i)
		{
			auto neighbour = neighbours[i];

			if (std::find(closedSet.begin(), closedSet.end(), neighbour) == closedSet.end())			// if closedset already has neighbour, skip evaluating this neighbour
			{
				auto tempG = current->g + 1;

				if (std::find(openSet.begin(), openSet.end(), neighbour) != closedSet.end())			// if openset has neighbour, evaluate this neighbour
				{
					if (tempG < neighbour->g)
						neighbour->g = tempG;	
				}
				else																					// if openset doesnt have this neighbour, add it in openset
				{
					neighbour->g = tempG;
					openSet.push_back(neighbour);
				}
			}

			neighbour->h = heuristic(neighbour, end);
			neighbour->f = neighbour->g + neighbour->h;

			neighbour->setPrevious(current);
		}
	}

	return false;
}

int PathFinder::heuristic(Node* start, Node* end)
{
	unsigned int x = end->i - start->i;
	unsigned int y = end->j - start->j;

	auto xy = x*x + y*y;

	return sqrt(xy);
}
