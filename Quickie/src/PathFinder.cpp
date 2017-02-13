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

	Node* bestMove = determineNextMove();

	auto neighbours = end->getNeighbours();
	if (std::find(neighbours.begin(), neighbours.end(), start) == neighbours.end())
	{
		double x = bestMove->pos.x - start->pos.x;
		double y = bestMove->pos.y - start->pos.y;

		ai->velocity.x = x;
		ai->velocity.y = y;
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

Node* PathFinder::determineNextMove()
{
	if (start != nullptr && end != nullptr)
	{
		//std::vector<Node*>					openSet;				// unevaluated nodes
		// std::vector<Node*>					closedSet;				// evaluated nodes
		// evaluated means that it has been checked if it is an efficient path towards the end

		//openSet.push_back(start);
		//path.clear();
		//while (!openSet.empty())
		//{
		//for (auto i = 0; i < openSet.size(); ++i)
		//{
		//	if (openSet[i]->f <= openSet[best]->f)
		//	{
		//		best = i;
		//	}
		//}

		//auto current = openSet[best];
		//if (current == end)
		//{
		//	auto temp = current;
		//	path.push_back(temp);

		//	while (temp->getprevious() != nullptr)
		//	{
		//		path.push_back(temp->getprevious());
		//		temp = temp->getprevious();
		//	}
		//	return true;
		//}

		//openSet.erase(std::find(openSet.begin(), openSet.end(), current));
		// closedSet.push_back(current);

		auto best = 0;
		auto neighbours = start->getNeighbours();
		for (auto i = 0; i < neighbours.size(); ++i)
		{
			auto neighbour = neighbours[i];

			// if closedset already has neighbour or is an obstacle, skip evaluating this neighbour
			if (neighbour->getCurrentObject() != nodeNS::OBJECT_TYPE_OBSTACLE)
			{
				auto tempG = start->g + 1;

				//auto newPath = false;
				//if (std::find(neighbours.begin(), neighbours.end(), neighbour) != neighbours.end())			// if current Node has neighbour, evaluate this neighbour
				//{
					if (tempG < neighbour->g)
					{
						neighbour->g = tempG;
						//newPath = true;
					}
				//}
				//else																				// if openset doesnt have this neighbour, add it in openset
				//{
				//	neighbour->g = tempG;
				//	newPath = true;
				//	openSet.push_back(neighbour);
				//}

				//if (newPath)
				//{
					neighbour->h = heuristic(neighbour, end);
					neighbour->f = neighbour->g + neighbour->h;

					if (neighbours[i]->f <= neighbours[best]->f)
						best = i;
					//neighbour->setPrevious(current);

				//}
			}
			
		}
		return neighbours[best];
	//}
	}

	return nullptr;
}

double PathFinder::heuristic(Node* initial, Node* target) const
{
	unsigned int x = target->i - initial->i;
	unsigned int y = target->j - initial->j;

	auto xy = x*x + y*y;
	return sqrt(xy);
}