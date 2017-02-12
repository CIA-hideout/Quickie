#include "Node.h"

Node::Node(D3DXVECTOR3& pos, D3DXVECTOR3& dimension, D3DXVECTOR3& scale, D3DXVECTOR3& color) : VertexShape() {

	graphics = nullptr;
	input = nullptr;
	previous = nullptr;
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

	D3DXCreateMeshFVF(12, 24, D3DXMESH_MANAGED, CUSTOMFVF, graphics->get3Ddevice(), &meshPtr);

	meshPtr->LockVertexBuffer(0, (void**)&vertices);

	// 0
	vertices[0] = { -dimension.x / ASPECT_RATIO / 2, -dimension.y / 2, -dimension.z / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(color.x), (int)(color.y), (int)(color.z)) };
	// 1
	vertices[1] = { -dimension.x / ASPECT_RATIO / 2, +dimension.y / 2, -dimension.z / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(color.x), (int)(color.y), (int)(color.z)) };
	// 2
	vertices[2] = { +dimension.x / ASPECT_RATIO / 2, +dimension.y / 2, -dimension.z / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(color.x), (int)(color.y), (int)(color.z)) };
	// 3
	vertices[3] = { +dimension.x / ASPECT_RATIO / 2, -dimension.y / 2, -dimension.z / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(color.x), (int)(color.y), (int)(color.z)) };
	// 4
	vertices[4] = { -dimension.x / ASPECT_RATIO / 2, -dimension.y / 2, +dimension.z / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(color.x), (int)(color.y), (int)(color.z)) };
	// 5
	vertices[5] = { -dimension.x / ASPECT_RATIO / 2, +dimension.y / 2, +dimension.z / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(color.x), (int)(color.y), (int)(color.z)) };
	// 6
	vertices[6] = { +dimension.x / ASPECT_RATIO / 2, +dimension.y / 2, +dimension.z / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(color.x), (int)(color.y), (int)(color.z)) };
	// 7
	vertices[7] = { +dimension.x / ASPECT_RATIO / 2, -dimension.y / 2, +dimension.z / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(color.x), (int)(color.y), (int)(color.z)) };

	meshPtr->UnlockVertexBuffer();

	vertexCount = 8;

	meshPtr->LockIndexBuffer(0, (void**)&indices);

	// front
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;
	// back
	indices[6] = 4; indices[7] = 6; indices[8] = 5;
	indices[9] = 4; indices[10] = 7; indices[11] = 6;
	// left
	indices[12] = 4; indices[13] = 5; indices[14] = 1;
	indices[15] = 4; indices[16] = 1; indices[17] = 0;
	// right
	indices[18] = 3; indices[19] = 2; indices[20] = 6;
	indices[21] = 3; indices[22] = 6; indices[23] = 7;
	// top
	indices[24] = 1; indices[25] = 5; indices[26] = 6;
	indices[27] = 1; indices[28] = 6; indices[29] = 2;
	// bottom
	indices[30] = 4; indices[31] = 0; indices[32] = 3;
	indices[33] = 4; indices[34] = 3; indices[35] = 7;

	meshPtr->UnlockIndexBuffer();

	indicesCount = 36;

	visible = false;
	alive = true;
}

void Node::draw(D3DXMATRIX& worldMat)
{
	if (visible) {
		LPDIRECT3DVERTEXBUFFER9 vBuffer;
		LPDIRECT3DINDEXBUFFER9 iBuffer;
		meshPtr->GetVertexBuffer(&vBuffer);
		meshPtr->GetIndexBuffer(&iBuffer);
		this->graphics->get3Ddevice()->SetStreamSource(0, vBuffer, 0, sizeof(LVertex));
		this->graphics->get3Ddevice()->SetIndices(iBuffer);

		D3DXMatrixRotationYawPitchRoll(&matRot, rotation.y, rotation.z, rotation.x);
		D3DXMatrixTranslation(&worldMat, pos.x, pos.y, pos.z);

		this->graphics->get3Ddevice()->SetTransform(D3DTS_WORLD, &(matRot * worldMat));
		meshPtr->DrawSubset(0);
	}
}

void Node::update(std::vector<VertexShape*>& vS, Player* player, AI* ai)
{
	QLine* qTemp;
	D3DXVECTOR3 poi;

	// detect what's in the node
	detectedObject = nodeNS::OBJECT_TYPE_NODE;

	if (currentObject != nodeNS::OBJECT_TYPE_OBSTACLE)
	{
		checkObstaclesCollision(vS, true);			// true, check for x-axis
		checkObstaclesCollision(vS, false);			// false, check for y-axis
	}
	
	if (currentObject != nodeNS::OBJECT_TYPE_QLINE)
	{
		for (auto i = 0; i < vS.size(); i++)
		{
			if (vS[i]->objectType == nodeNS::OBJECT_TYPE_QLINE)
			{
				qTemp = (QLine*)vS[i];
				if (qTemp->parent != this)
				{
					if (CollisionManager::collidePixelPerfect(poi, this, vS[i])) {
						detectedObject = nodeNS::OBJECT_TYPE_QLINE;
						break;
					}
				}
			}
		}
	}

	if (currentObject != nodeNS::OBJECT_TYPE_AI)
	{
		if (CollisionManager::collideAABB(this, ai))
		{
			detectedObject = nodeNS::OBJECT_TYPE_AI;
		}
	}

	if (currentObject != nodeNS::OBJECT_TYPE_PLAYER)
	{
		if (CollisionManager::collideAABB(this, player))
		{
			detectedObject = nodeNS::OBJECT_TYPE_PLAYER;
		}
	}

	switch (detectedObject)
	{
	case nodeNS::OBJECT_TYPE_OBSTACLE:
		currentObject = nodeNS::OBJECT_TYPE_OBSTACLE;
		break;

	case nodeNS::OBJECT_TYPE_PLAYER:
		currentObject = nodeNS::OBJECT_TYPE_PLAYER;
		break;

	case nodeNS::OBJECT_TYPE_QLINE:
		currentObject = nodeNS::OBJECT_TYPE_QLINE;
		break;

	case nodeNS::OBJECT_TYPE_AI:
		currentObject = nodeNS::OBJECT_TYPE_AI;
		break;

	case nodeNS::OBJECT_TYPE_NODE:
		currentObject = nodeNS::OBJECT_TYPE_NODE;
		visible = false;
		break;
	}

	previous = nullptr;
}

void Node::setNeighbours(std::vector<std::vector<Node>>* nV)
{
	if (i < cameraNS::cols - 1)
		neighbours.push_back(&nV->at(i + 1).at(j));			// right neighbour

	if (i > 0)
		neighbours.push_back(&nV->at(i - 1).at(j));			// left neighbour
	
	if (j < cameraNS::rows - 1)
		neighbours.push_back(&nV->at(i).at(j + 1));			// top neighbour
	
	if (j > 0)
		neighbours.push_back(&nV->at(i).at(j - 1));			// bottom neighbour
	
	if (i > 0 && j > 0)
		neighbours.push_back(&nV->at(i - 1).at(j - 1));		// top left neighbour
	
	if (i < cameraNS::cols - 1 && j > 0)
		neighbours.push_back(&nV->at(i + 1).at(j - 1));		// top right neighbour
	
	if (i > 0 && j < cameraNS::rows - 1)
		neighbours.push_back(&nV->at(i - 1).at(j + 1));		// bottom left neighbour
	
	if (i < cameraNS::cols - 1 && j < cameraNS::rows - 1)
		neighbours.push_back(&nV->at(i + 1).at(j + 1));		// bottom right neighbour
}

void Node::checkObstaclesCollision(std::vector<VertexShape*>& vS, bool x)
{
	if (x)
	{
		for (auto i = 0; i < vS.size(); i++) {
			if (vS[i]->id != id && (vS[i]->objectType == OBJECT_TYPE_OBSTACLE)) {
				if (CollisionManager::collideAABB(this, vS[i])) {
					detectedObject = nodeNS::OBJECT_TYPE_OBSTACLE;
					break;
				}
			}
		}
	}
	else
	{
		for (auto i = 0; i < vS.size(); i++) {
			if (vS[i]->id != id && (vS[i]->objectType == OBJECT_TYPE_OBSTACLE)) {
				if (CollisionManager::collideAABB(this, vS[i])) {
					detectedObject = nodeNS::OBJECT_TYPE_OBSTACLE;
					break;
				}
			}
		}
	}
}