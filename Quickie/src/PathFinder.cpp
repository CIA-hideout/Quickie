#include "PathFinder.h"

PathFinder::PathFinder()
{
	start = nullptr;
	end = nullptr;
	graphics = nullptr;
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
		
		for (int y = cameraNS::y; y >= -cameraNS::y; --y)
		{
			Node temp = Node(D3DXVECTOR3(x, y, playerNS::z), D3DXVECTOR3(2, 2, 2), D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 240, 0));
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

void PathFinder::update(std::vector<VertexShape*>& vS, Player* target, AI* ai)
{
	for (auto x = 0; x <nodesOnScreen.size(); ++x)
	{
		std::vector<Node>* pVect = &nodesOnScreen.at(x);

		for (auto y = 0; y < pVect->size(); ++y)
		{
			Node* temp = &pVect->at(y);
			temp->update(vS, target, ai);

			if (temp->getCurrentObject() == nodeNS::OBJECT_TYPE_AI)		// set AI as start
				start = temp;

			if (temp->getCurrentObject() == nodeNS::OBJECT_TYPE_PLAYER)		// set Player as end
			end = temp;

		}
	}

	if(determinePath())
	{
		// do stuff e.g. move AI to target

		for (auto i = 0; i < path.size(); ++i)
		{
			path.at(i)->visible = true;
		}
	}
	else
	{
		// no possible path found
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
	if (start != nullptr && end != nullptr)
	{
		std::vector<Node*>					openSet;				// unevaluated nodes
		std::vector<Node*>					closedSet;				// evaluated nodes
		// evaluated means that it has been checked if it is an efficient path towards the end

		openSet.push_back(start);
		path.clear();
		auto n = 0; //
		while (!openSet.empty())
		{
			auto best = 0;
			for (auto i = 0; i < openSet.size(); ++i)
			{
				if (openSet[i]->f <= openSet[best]->f)
				{
					best = i;
				}
			}

			auto current = openSet[best];
			n++;
			if (current == end)
			{
				auto temp = current;
				path.push_back(temp);

				while (temp->getprevious() != nullptr)
				{
					path.push_back(temp->getprevious());
					temp = temp->getprevious();
				}
				return true;
			}

			openSet.erase(std::find(openSet.begin(), openSet.end(), current));
			closedSet.push_back(current);

			auto neighbours = current->getNeighbours();
			for (auto i = 0; i < neighbours.size(); ++i)
			{
				auto neighbour = neighbours[i];

				// if closedset already has neighbour or is an obstacle, skip evaluating this neighbour
				if (std::find(closedSet.begin(), closedSet.end(), neighbour) == closedSet.end() && neighbour->getCurrentObject() != nodeNS::OBJECT_TYPE_OBSTACLE)
				{
					auto tempG = current->g + 1;

					auto newPath = false;
					if (std::find(openSet.begin(), openSet.end(), neighbour) != openSet.end())			// if openset has neighbour, evaluate this neighbour
					{
						if (tempG < neighbour->g)
						{
							neighbour->g = tempG;
							newPath = true;
						}
					}
					else																				// if openset doesnt have this neighbour, add it in openset
					{
						neighbour->g = tempG;
						newPath = true;
						openSet.push_back(neighbour);
					}

					if (newPath)
					{
						neighbour->h = heuristic(neighbour, end);
						neighbour->f = neighbour->g + neighbour->h;

						neighbour->setPrevious(current);
					}
				}
			}
		}
	}
	return false;
}

double PathFinder::heuristic(Node* initial, Node* target) const
{
	unsigned int x = target->i - initial->i;
	unsigned int y = target->j - initial->j;

	auto xy = x*x + y*y;
	return sqrt(xy);
}