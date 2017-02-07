#include "Wall.h"

Wall::Wall(D3DXVECTOR3& pos, D3DXVECTOR3& dimension, D3DXVECTOR3& scale, D3DXVECTOR3& color) : Obstacle() {

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

	objectType = OBJECT_TYPE_WALL;

	velocity.x = 0;
	velocity.y = 0;
}

Wall::~Wall() {

}
