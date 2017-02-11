#pragma once

#include "Node.h"
#include "graphics.h"

class PathFinder
{
	Node*					start;
	Node*					end;
	Graphics*				graphics;

	std::vector<std::vector<Node>>		nodesOnScreen;
	std::vector<Node*>					path;
	std::vector<Node*>					openSet;				// unevaluated nodes
	std::vector<Node*>					closedSet;				// evaluated nodes
																// evaluated means that it has been checked if it is an efficient path towards the end

public:


	PathFinder();
	~PathFinder();

	void initialize(Graphics* graphics);
	void update(std::vector<VertexShape*>& , Player* player);			// update the start, end and path
	void draw(D3DXMATRIX& worldMatrix);					// for testing purposes
	void setTargetNode(Node* target);
	bool determinePath();								// set the most efficient path based on the target
	int heuristic(Node* start, Node* end);				// determine the efficiency of a path
};