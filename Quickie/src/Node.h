#pragma once
#include "Player.h"
#include "AI.h"

namespace nodeNS
{
	enum ObjectType
	{
		OBJECT_TYPE_PLAYER,
		OBJECT_TYPE_OBSTACLE,
		OBJECT_TYPE_QLINE,
		OBJECT_TYPE_NODE,
		OBJECT_TYPE_AI
	};
}

class Node : public VertexShape
{
protected:

	nodeNS::ObjectType					currentObject = nodeNS::OBJECT_TYPE_NODE;
	nodeNS::ObjectType					detectedObject = nodeNS::OBJECT_TYPE_NODE;
	std::vector<Node*>					neighbours;
	Node*								previous;
	bool								target;

public:
	int i = 0, j = 0;
	double f = 0, g = 0, h = 0;

	Node() = default;
	Node(D3DXVECTOR3& pos, D3DXVECTOR3& dimension, D3DXVECTOR3& scale, D3DXVECTOR3& color);
	virtual ~Node();

	void init(Graphics*);
	void draw(D3DXMATRIX&) override;
	void update(std::vector<VertexShape*>& vS, Player* player, AI* ai);

	void checkObstaclesCollision(std::vector<VertexShape*>& vS, bool x);

	void setNeighbours(std::vector<std::vector<Node>>* nodesOnScreen);
	void setPrevious(Node* p){ previous = p; }
	void setCurrentObject(nodeNS::ObjectType o){ currentObject = o; }
	
	std::vector<Node*>	getNeighbours() const { return neighbours; }
	Node*				getprevious() const { return previous; }
	nodeNS::ObjectType	getCurrentObject() const { return currentObject; }
};