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

public:


	PathFinder();
	~PathFinder();

	void initialize(Graphics* graphics);
	void update(std::vector<VertexShape*>& , Player* target, AI* start);			// update the start, end and path
	void draw(D3DXMATRIX& worldMatrix);					// for testing purposes
	bool determinePath();								// set the most efficient path based on the target
	double heuristic(Node* start, Node* end) const;				// determine the efficiency of a path
};