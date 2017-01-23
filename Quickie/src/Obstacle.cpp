#include "Obstacle.h"
#include <algorithm>

int minMaxRand(int min, int max);

Obstacle::Obstacle(D3DXVECTOR3& pos, D3DXVECTOR3& dimension, D3DXVECTOR3& scale, D3DXVECTOR3& color) : VertexShape() {

	memcpy(this->pos, pos, sizeof(D3DXVECTOR3));
	memcpy(this->dimension, dimension, sizeof(D3DXVECTOR3));
	memcpy(this->scale, scale, sizeof(D3DXVECTOR3));
	memcpy(this->color, color, sizeof(D3DXVECTOR3));

	min.x = 0;
	min.y = 0;
	min.z = 0;

	min.x = 0;
	min.y = 0;
	min.z = 0;

	rotation.x = 0;
	rotation.y = 0;
	rotation.z = 0;

	collisionType = CT_AABB;

	velocity.x = 0;
	velocity.y = 0;
	velocity.z = 0;

	

}

Obstacle::Obstacle(D3DXVECTOR3& pos) : VertexShape()
{
	memcpy(this->pos, pos, sizeof(D3DXVECTOR3));

	D3DXVECTOR3& dimension = setDimension();
	memcpy(this->dimension, dimension, sizeof(D3DXVECTOR3));

	D3DXVECTOR3& scale = D3DXVECTOR3(1, 1, 1);
	memcpy(this->scale, scale, sizeof(D3DXVECTOR3));

	D3DXVECTOR3& color = getRandomColor();
	memcpy(this->color, color, sizeof(D3DXVECTOR3));

	min.x = 0;
	min.y = 0;
	min.z = 0;

	min.x = 0;
	min.y = 0;
	min.z = 0;

	rotation.x = 0;
	rotation.y = 0;
	rotation.z = 0;

	collisionType = CT_AABB;

	velocity.x = 0;
	velocity.y = 0;
	velocity.z = 0;
}

Obstacle::~Obstacle() {

}

void Obstacle::init(Game* gamePtr) {

	this->graphics = gamePtr->getGraphics();
	D3DXCreateMeshFVF(12, 24, D3DXMESH_MANAGED, CUSTOMFVF, gamePtr->getGraphics()->get3Ddevice(), &meshPtr);

	vertices = 0;
	meshPtr->LockVertexBuffer(0, (void**)&vertices);

	// 0
	vertices[0] = { -dimension.x / ASPECT_RATIO / 2, -dimension.y / 2, -dimension.z / 2, D3DCOLOR_XRGB((int)(color.x), (int)(color.y), (int)(color.z)) };
	// 1						 
	vertices[1] = { -dimension.x / ASPECT_RATIO / 2, +dimension.y / 2, -dimension.z / 2, D3DCOLOR_XRGB((int)(color.x), (int)(color.y), (int)(color.z)) };
	// 2						 
	vertices[2] = { +dimension.x / ASPECT_RATIO / 2, +dimension.y / 2, -dimension.z / 2, D3DCOLOR_XRGB((int)(color.x), (int)(color.y), (int)(color.z)) };
	// 3						 
	vertices[3] = { +dimension.x / ASPECT_RATIO / 2, -dimension.y / 2, -dimension.z / 2, D3DCOLOR_XRGB((int)(color.x), (int)(color.y), (int)(color.z)) };
	// 4						 
	vertices[4] = { -dimension.x / ASPECT_RATIO / 2, -dimension.y / 2, +dimension.z / 2, D3DCOLOR_XRGB((int)(color.x), (int)(color.y), (int)(color.z)) };
	// 5						 
	vertices[5] = { -dimension.x / ASPECT_RATIO / 2, +dimension.y / 2, +dimension.z / 2, D3DCOLOR_XRGB((int)(color.x), (int)(color.y), (int)(color.z)) };
	// 6						 
	vertices[6] = { +dimension.x / ASPECT_RATIO / 2, +dimension.y / 2, +dimension.z / 2, D3DCOLOR_XRGB((int)(color.x), (int)(color.y), (int)(color.z)) };
	// 7						 
	vertices[7] = { +dimension.x / ASPECT_RATIO / 2, -dimension.y / 2, +dimension.z / 2, D3DCOLOR_XRGB((int)(color.x), (int)(color.y), (int)(color.z)) };

	meshPtr->UnlockVertexBuffer();

	vertexCount = 8;

	indices = 0;
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
	// rindicesght
	indices[18] = 3; indices[19] = 2; indices[20] = 6;
	indices[21] = 3; indices[22] = 6; indices[23] = 7;
	// top
	indices[24] = 1; indices[25] = 5; indices[26] = 6;
	indices[27] = 1; indices[28] = 6; indices[29] = 2;
	// bottom
	indices[30] = 4; indices[31] = 0; indices[32] = 3;
	indices[33] = 4; indices[34] = 3; indices[35] = 7;

	meshPtr->UnlockIndexBuffer();

}

void Obstacle::draw(D3DXMATRIX& worldMat) {

	D3DXMATRIX matRot;
	D3DXMATRIX matTemp;

	LPDIRECT3DVERTEXBUFFER9 vBuffer;
	LPDIRECT3DINDEXBUFFER9 iBuffer;
	meshPtr->GetVertexBuffer(&vBuffer);
	meshPtr->GetIndexBuffer(&iBuffer);
	graphics->get3Ddevice()->SetStreamSource(0, vBuffer, 0, sizeof(LVertex));
	graphics->get3Ddevice()->SetIndices(iBuffer);

	D3DXMatrixRotationYawPitchRoll(&matRot, rotation.y, rotation.z, rotation.x);

	D3DXMatrixTranslation(&worldMat, pos.x, pos.y, pos.z);

	matTemp = matRot * worldMat;

	graphics->get3Ddevice()->SetTransform(D3DTS_WORLD, &matTemp);
	meshPtr->DrawSubset(0);

}

void Obstacle::update(float deltaTime) {
	
	// pos.y -= 0.1f; // go down
	
	//if (pos.y <= -25) {
	//	pos.y = 20 + minMaxRand(0, 2);
	//	pos.x = minMaxRand(-15, 15);

	//	color = getRandomColor();
	//	setColor(color);
	//}

}

int minMaxRand(int min, int max) {
	return rand() % (max - min + 1) + min;
}

D3DXVECTOR3 Obstacle::getRandomColor()
{
	std::srand(unsigned(std::time(nullptr)));

	// array is not dynamic use vector instead
	std::vector<D3DXVECTOR3> color;
	color.push_back(COLOR_RED);
	color.push_back(COLOR_YELLOW);
	color.push_back(COLOR_PURPLE);
	color.push_back(COLOR_GREEN);
	color.push_back(COLOR_BLUE);
	color.push_back(COLOR_WHITE);

	std::random_shuffle(color.begin(), color.end()); // randomise vector content


	return color.front();	//use first value of randomise array
}

void Obstacle::setColor(D3DXVECTOR3 newColor)
{
	LVertex* v;
	meshPtr->LockVertexBuffer(0, (void**)&v);

	for (int i = 0; i < vertexCount; i++) {
		v->color = D3DCOLOR_RGBA( (int) newColor.x, (int)newColor.y, 
			(int) newColor.z, 255);
		v++;
	}

	meshPtr->UnlockIndexBuffer();

}

D3DXVECTOR3 Obstacle::setDimension()
{
	std::srand(unsigned(std::time(nullptr)));

	std::vector<D3DXVECTOR3> dimensions;
	dimensions.push_back(DIMENSTION_SMALL);
	dimensions.push_back(DIMENSTION_MEDIUM);
	dimensions.push_back(DIMENSTION_MEDIUM);
	// medium size to appear more frequently

	std::random_shuffle(dimensions.begin(), dimensions.end()); //ramdomise vector
	return dimensions.front(); // use first value of random vector
}
