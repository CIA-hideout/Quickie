#include "Obstacle.h"
#include <algorithm>
#include <random>

Obstacle::Obstacle(D3DXVECTOR3& pos, D3DXVECTOR3& dimension, D3DXVECTOR3& scale, D3DXVECTOR3& color) : VertexShape() {
	static int obstacleCount = 0;
	obstacleId = obstacleCount++;

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

	objectType = OBJECT_TYPE_OBSTACLE;

	velocity.x = 0;
	velocity.y = 0;
}

Obstacle::~Obstacle() {
}

void Obstacle::init(Audio* audio, Graphics* graphics) {
	this->graphics = graphics;
	this->audio = audio;

	D3DXCreateMeshFVF(12, 24, D3DXMESH_MANAGED, CUSTOMFVF, graphics->get3Ddevice(), &meshPtr);

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

void Obstacle::update(float deltaTime, std::vector<VertexShape*> players) {
	timer += deltaTime;

	switch (currentState)
	{
	case INACTIVE:
		// change to new position
		setPosition(newPos);

		if (newPos != DIMENSION_NON_EXISTANT)
			currentState = GROW;
		break;

	case ACTIVE:
		break;

	case SHRINK:
		// update size of obstacle
		if (timer >= 0.05f) {
			if (!CollisionManager::collideAABB(this, players[0]) || !CollisionManager::collideAABB(this, players[1]))
				D3DXMatrixScaling(&matScale, 0.5f, 0.5f, 0.5f);	//matrix for shrinking
			D3DXVec3TransformCoord(&dimension, &dimension, &matScale);
			setDimension(dimension);

			/* Avoid Zeno Dichotomy Paradox
			* If you divide by half and so on repeatedly,
			* you will continue dividing forever and never reach the end.
			* So we will set dimensions to 0, when we hit a number close to 0
			*/
			if (dimension.x <= 0.01)
				dimension.x = 0;

			if (dimension.y <= 0.01)
				dimension.y = 0;

			if (dimension.z <= 0.01)
				dimension.z = 0;

			if (dimension == DIMENSION_NON_EXISTANT)
				currentState = INACTIVE;	// change to inactive when dimension are 0

			timer = 0;
		}
		break;

	case GROW:
		//for (int i = 0; i < players.size(); i++)

		//  0 * a real number is 0
		//	change dimensions to something which can be multiplied
		if (dimension == DIMENSION_NON_EXISTANT)
			setDimension(DIMENSION_ALMOST_ZERO);

		// update size of obstacle
		if (timer >= 0.05f)
		{
			D3DXMatrixScaling(&matScale, 1.5f, 1.5f, 1.5f); //matrix for growing
			D3DXVec3TransformCoord(&dimension, &dimension, &matScale);
			setDimension(dimension);
			timer = 0;

			if (dimension.x > newDimension.x)
				dimension.x = newDimension.x;

			if (dimension.y > newDimension.y)
				dimension.y = newDimension.y;

			if (dimension.z > newDimension.z)
				dimension.z = newDimension.z;

			if (dimension == newDimension)
				currentState = ACTIVE;	// change to active when dimension are the same
		}
		break;

	default: break;
	}
}

// Randomly generate a color and returns the value
D3DXVECTOR3 Obstacle::getRandomColor() {
	//std::srand(unsigned(std::time(nullptr)));

	// array is not dynamic use vector instead
	std::vector<D3DXVECTOR3> color;
	color.push_back(COLOR_RED);
	color.push_back(COLOR_YELLOW);
	color.push_back(COLOR_PURPLE);
	color.push_back(COLOR_GREEN);
	color.push_back(COLOR_BLUE);
	color.push_back(COLOR_WHITE);

	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::shuffle(color.begin(), color.end(), rng); // randomise vector content

	return color.front();	//use first value of randomise array
}

// set the obstructor to the given color
void Obstacle::setColor(D3DXVECTOR3 newColor) {
	LVertex* v;

	meshPtr->LockVertexBuffer(0, (void**)&v);

	for (int i = 0; i < vertexCount; i++) {
		v->color = D3DCOLOR_RGBA(int(newColor.x), int(newColor.y),
			int(newColor.z), 255);
		v++;
	}

	meshPtr->UnlockIndexBuffer();
}

// set position of obstacle
void Obstacle::setPosition(D3DXVECTOR3 newPos)
{
	pos.x = newPos.x;
	pos.y = newPos.y;
	pos.z = newPos.z;
}

// set Dimensions
void Obstacle::setDimension(D3DXVECTOR3 newDimension) {
	dimension = newDimension;

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
}

// generate a random size for the obstructor and returns the size
D3DXVECTOR3 Obstacle::getRandomDimension() {
	std::vector<D3DXVECTOR3> dimensions;
	dimensions.push_back(DIMENSION_HORIZONTAL_SMALL);
	dimensions.push_back(DIMENSION_HORIZONTAL_MEDIUM);
	dimensions.push_back(DIMENSION_HORIZONTAL_MEDIUM);
	// medium size to appear more frequently

	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::shuffle(dimensions.begin(), dimensions.end(), rng); //ramdomise vector

	return dimensions.front(); // use first value of random vector
}

void Obstacle::assign(rapidjson::Document& doc) {
	// store level 1 stuff
	lvl1Pos = D3DXVECTOR3(
		doc["obstacle"].GetArray()[obstacleId]["lvl_1_pos_x"].GetFloat(),
		doc["obstacle"].GetArray()[obstacleId]["lvl_1_pos_y"].GetFloat(),
		doc["obstacle"].GetArray()[obstacleId]["lvl_1_pos_z"].GetFloat()
		);
	lvl1Dim = assignDimension(
		doc["obstacle"].GetArray()[obstacleId]["lvl_1_dim"].GetInt());

	// store level 2 stuff
	lvl2Pos = D3DXVECTOR3(
		doc["obstacle"].GetArray()[obstacleId]["lvl_2_pos_x"].GetFloat(),
		doc["obstacle"].GetArray()[obstacleId]["lvl_2_pos_y"].GetFloat(),
		doc["obstacle"].GetArray()[obstacleId]["lvl_2_pos_z"].GetFloat()
		);
	lvl2Dim = assignDimension(
		doc["obstacle"].GetArray()[obstacleId]["lvl_2_dim"].GetInt());

	// store level 3 stuff
	lvl3Pos = D3DXVECTOR3(
		doc["obstacle"].GetArray()[obstacleId]["lvl_3_pos_x"].GetFloat(),
		doc["obstacle"].GetArray()[obstacleId]["lvl_3_pos_y"].GetFloat(),
		doc["obstacle"].GetArray()[obstacleId]["lvl_3_pos_z"].GetFloat()
		);
	lvl3Dim = assignDimension(
		doc["obstacle"].GetArray()[obstacleId]["lvl_3_dim"].GetInt());
}

D3DXVECTOR3 Obstacle::assignDimension(int type){
	switch (type) {
	case 0: return DIMENSION_HORIZONTAL_SMALL;
	case 1: return DIMENSION_HORIZONTAL_MEDIUM;
	case 2: return DIMENSION_HORIZONTAL_LARGE;
	case 3: return DIMENSION_VERTICAL_SMALL;
	case 4: return DIMENSION_VERTICAL_MEDIUM;
	case 5: return DIMENSION_VERTICAL_LARGE;
	case 6: return DIMENSION_NON_EXISTANT;
	}
}

void Obstacle::setLevel1(int count) {
	newPos = lvl1Pos;
	newDimension = lvl1Dim;

	if (count != 0)
		currentState = SHRINK;
}

void Obstacle::setLevel2(int count)
{
	newPos = lvl2Pos;
	newDimension = lvl2Dim;

	if (count != 0)
		currentState = SHRINK;
}

void Obstacle::setLevel3(int count)
{
	newPos = lvl3Pos;
	newDimension = lvl3Dim;

	if (count != 0)
		currentState = SHRINK;
}
