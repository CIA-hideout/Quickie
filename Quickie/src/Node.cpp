#include "Node.h"

Node::Node(D3DXVECTOR3& pos, D3DXVECTOR3& dimension, D3DXVECTOR3& scale, D3DXVECTOR3& color) : VertexShape() {

	graphics = nullptr;
	input = nullptr;
	health = maxHealth = 3;

	memcpy(this->pos, pos, sizeof(D3DXVECTOR3));
	memcpy(this->dimension, dimension, sizeof(D3DXVECTOR3));
	memcpy(this->scale, scale, sizeof(D3DXVECTOR3));
	memcpy(this->color, color, sizeof(D3DXVECTOR3));

	min.x = 0;
	min.y = 0;
	min.z = 0;

	rotation.x = 0;
	rotation.y = 0;
	rotation.z = 0;

	objectType = OBJECT_TYPE_NODE;

	velocity.x = 0;
	velocity.y = 0;
	velocity.z = 0;
}

Node::~Node(){};

void Node::init(Graphics* g)
{
	graphics = g;
}

void Node::draw(D3DXMATRIX& worldMat)
{
	
}

void Node::update(float deltaTime)
{
	
}
