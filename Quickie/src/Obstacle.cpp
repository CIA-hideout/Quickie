#include "Obstacle.h"


Obstacle::Obstacle(D3DXVECTOR3& pos, D3DXVECTOR3& dimension, D3DXVECTOR3& scale) : VertexShape() {

	memcpy(this->pos, pos, sizeof(D3DXVECTOR3));
	memcpy(this->dimension, dimension, sizeof(D3DXVECTOR3));
	memcpy(this->scale, scale, sizeof(D3DXVECTOR3));

}

Obstacle::~Obstacle() {

}

void Obstacle::init(Game* gamePtr) {

	this->graphics = gamePtr->getGraphics();
	D3DXCreateMeshFVF(12, 24, D3DXMESH_MANAGED, CUSTOMFVF, gamePtr->getGraphics()->get3Ddevice(), &meshPtr);

	LVertex* v_ = 0;
	meshPtr->LockVertexBuffer(0, (void**)&v_);

	// 0
	v_[0] = { pos.x - dimension.x / 2, pos.y - dimension.y / 2, pos.z - dimension.z / 2, D3DCOLOR_XRGB(255, 255, 255) };
	// 1
	v_[1] = { pos.x - dimension.x / 2, pos.y + dimension.y / 2, pos.z - dimension.z / 2, D3DCOLOR_XRGB(255, 255, 255) };
	// 2
	v_[2] = { pos.x + dimension.x / 2, pos.y + dimension.y / 2, pos.z - dimension.z / 2, D3DCOLOR_XRGB(255, 255, 255) };
	// 3
	v_[3] = { pos.x + dimension.x / 2, pos.y - dimension.y / 2, pos.z - dimension.z / 2, D3DCOLOR_XRGB(255, 255, 255) };
	// 4
	v_[4] = { pos.x - dimension.x / 2, pos.y - dimension.y / 2, pos.z + dimension.z / 2, D3DCOLOR_XRGB(255, 255, 255) };
	// 5
	v_[5] = { pos.x - dimension.x / 2, pos.y + dimension.y / 2, pos.z + dimension.z / 2, D3DCOLOR_XRGB(255, 255, 255) };
	// 6
	v_[6] = { pos.x + dimension.x / 2, pos.y + dimension.y / 2, pos.z + dimension.z / 2, D3DCOLOR_XRGB(255, 255, 255) };
	// 7
	v_[7] = { pos.x + dimension.x / 2, pos.y - dimension.y / 2, pos.z + dimension.z / 2, D3DCOLOR_XRGB(255, 255, 255) };

	meshPtr->UnlockVertexBuffer();

	WORD* i = 0;
	meshPtr->LockIndexBuffer(0, (void**)&i);

	// front
	i[0] = 0; i[1] = 1; i[2] = 2;
	i[3] = 0; i[4] = 2; i[5] = 3;
	// back
	i[6] = 4; i[7] = 6; i[8] = 5;
	i[9] = 4; i[10] = 7; i[11] = 6;
	// left
	i[12] = 4; i[13] = 5; i[14] = 1;
	i[15] = 4; i[16] = 1; i[17] = 0;
	// right
	i[18] = 3; i[19] = 2; i[20] = 6;
	i[21] = 3; i[22] = 6; i[23] = 7;
	// top
	i[24] = 1; i[25] = 5; i[26] = 6;
	i[27] = 1; i[28] = 6; i[29] = 2;
	// bottom
	i[30] = 4; i[31] = 0; i[32] = 3;
	i[33] = 4; i[34] = 3; i[35] = 7;

	meshPtr->UnlockIndexBuffer();

}

void Obstacle::draw() {

	static float rotation = 0.0f;

	rotation += 0.01f;

	LPDIRECT3DVERTEXBUFFER9 vBuffer;
	LPDIRECT3DINDEXBUFFER9 iBuffer;
	meshPtr->GetVertexBuffer(&vBuffer);
	meshPtr->GetIndexBuffer(&iBuffer);
	graphics->get3Ddevice()->SetStreamSource(0, vBuffer, 0, sizeof(LVertex));
	graphics->get3Ddevice()->SetIndices(iBuffer);

	D3DXMATRIX matTemp;
	D3DXMATRIX matRot;
	D3DXMATRIX matWorld;

	D3DXMatrixTranslation(&matWorld, pos.x, pos.y, pos.z);
	D3DXMatrixIdentity(&matRot);

	D3DXMatrixRotationX(&matTemp, 0);
	D3DXMatrixMultiply(&matRot, &matRot, &matTemp);
	D3DXMatrixRotationY(&matTemp, 0);
	D3DXMatrixMultiply(&matRot, &matRot, &matTemp);
	D3DXMatrixRotationZ(&matTemp, 0);
	D3DXMatrixMultiply(&matRot, &matRot, &matTemp);

	D3DXMatrixMultiply(&matWorld, &matRot, &matWorld);

	graphics->get3Ddevice()->SetTransform(D3DTS_WORLD, &matWorld);
	graphics->get3Ddevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	meshPtr->DrawSubset(0);

	D3DXMatrixTranslation(&matWorld, 0, 0, 0);
	graphics->get3Ddevice()->SetTransform(D3DTS_WORLD, &matWorld);

}

void Obstacle::update(float deltaTime) {

}