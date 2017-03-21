#pragma once

#include "Node.h"
#include <stack>

class NodeManager
{
	Node*					start;
	Node*					end;
	Node*					player;

public:

	std::vector<std::vector<Node>>		nodesOnScreen;
	std::vector<Node*>					obstacleNodes;
	std::vector<Node*>					emptyNodes;
	std::vector<Node*>					closedSet;			// nodes previously traversed through in one path

	void initialize(Graphics*);
	void update(std::vector<VertexShape*>& vS, Player* sqr1, AI* computer);
	void draw(D3DXMATRIX worldMatrix);

	Node* determineBestNode();									// set the most efficient path based on the target
	double heuristic(Node* start, Node* end) const;				// determine the efficiency of a path
	void setTarget(nodeNS::ObjectType);

	void setStart(Node* n){ start = n; }
	void setEnd(Node* n){ end = n; }
	void setPlayer(Node* n){ player = n; }

	Node* getEnd() { return end; }
	Node* getStart(){ return start; }
	Node* setPlayer(){ return player; }
};
