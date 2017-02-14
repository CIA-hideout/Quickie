#pragma once

#include "Node.h"
#include "graphics.h"

namespace behaviourNS
{
	const int targetsNum = 3;
	const int behaviourNum = 4;
	const int behaviourRand = 1000;
	const int baseRand = 100;
	const int range = 5;

	enum Type
	{
		TARGET_PLAYER,
		RUN,
		HIDE,
		STOP
	};
}

class Behaviour
{
	Node*					start;
	Node*					end;
	Node*					player;
	AI*						computer;
	Graphics*				graphics;

	behaviourNS::Type					currentBehaviour;
	std::vector<std::vector<Node>>		nodesOnScreen;
	std::vector<Node*>					obstacleNodes;
	std::vector<Node*>					emptyNodes;

public:


	Behaviour();
	~Behaviour();

	void initialize(Graphics* graphics, AI* computer);
	void update(std::vector<VertexShape*>& , Player* target);			// update the start, end
	void draw(D3DXMATRIX& worldMatrix);					// for testing purposes
	void setTarget(nodeNS::ObjectType);
	void checkObstacles();
	Node* determineNextMove();								// set the most efficient path based on the target
	double heuristic(Node* start, Node* end) const;				// determine the efficiency of a path

	void act(std::vector<VertexShape*>& vS);
	void randBehaviour();
	//void modifiedRandBehaviour(float modifier, behaviourNS::Type selector);

	Node* getEnd() { return end; }
	Node* getStart(){ return start; }
};