#include "GUIBar.h"

GUIBar::GUIBar(VertexShape* parent, D3DXVECTOR3& color) : VertexShape() {

	this->color = color;
	this->parent = parent;

	this->scale.x = 1;
	this->scale.y = 0.1;
	this->scale.z = 0.1;

	objectType = OBJECT_TYPE_GUI_BAR;

}

void GUIBar::init(Graphics* graphics) {

	this->graphics = graphics;

	D3DXCreateMeshFVF(12, 24, D3DXMESH_MANAGED, CUSTOMFVF, graphics->get3Ddevice(), &meshPtr);

	meshPtr->LockVertexBuffer(0, (void**)&vertices);

	vertices[0] = { -parent->dimension.x / ASPECT_RATIO / 2, -parent->dimension.y / 2, -parent->dimension.z / 2, D3DCOLOR_XRGB((int)(color.x), (int)(color.y), (int)(color.z)) };
	// 1
	vertices[1] = { -parent->dimension.x / ASPECT_RATIO / 2, +parent->dimension.y / 2, -parent->dimension.z / 2, D3DCOLOR_XRGB((int)(color.x), (int)(color.y), (int)(color.z)) };
	// 2
	vertices[2] = { +parent->dimension.x / ASPECT_RATIO / 2, +parent->dimension.y / 2, -parent->dimension.z / 2, D3DCOLOR_XRGB((int)(color.x), (int)(color.y), (int)(color.z)) };
	// 3
	vertices[3] = { +parent->dimension.x / ASPECT_RATIO / 2, -parent->dimension.y / 2, -parent->dimension.z / 2, D3DCOLOR_XRGB((int)(color.x), (int)(color.y), (int)(color.z)) };
	// 4
	vertices[4] = { -parent->dimension.x / ASPECT_RATIO / 2, -parent->dimension.y / 2, +parent->dimension.z / 2, D3DCOLOR_XRGB((int)(color.x), (int)(color.y), (int)(color.z)) };
	// 5
	vertices[5] = { -parent->dimension.x / ASPECT_RATIO / 2, +parent->dimension.y / 2, +parent->dimension.z / 2, D3DCOLOR_XRGB((int)(color.x), (int)(color.y), (int)(color.z)) };
	// 6
	vertices[6] = { +parent->dimension.x / ASPECT_RATIO / 2, +parent->dimension.y / 2, +parent->dimension.z / 2, D3DCOLOR_XRGB((int)(color.x), (int)(color.y), (int)(color.z)) };
	// 7
	vertices[7] = { +parent->dimension.x / ASPECT_RATIO / 2, -parent->dimension.y / 2, +parent->dimension.z / 2, D3DCOLOR_XRGB((int)(color.x), (int)(color.y), (int)(color.z)) };

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

void GUIBar::update(float deltaTime) {
	
}

void GUIBar::draw(D3DXMATRIX& worldMat) {

	if (visible)
	{
		LPDIRECT3DVERTEXBUFFER9 vBuffer;
		LPDIRECT3DINDEXBUFFER9 iBuffer;

		D3DXMATRIX scaleMat;
		D3DXMATRIX transMat;

		meshPtr->GetVertexBuffer(&vBuffer);
		meshPtr->GetIndexBuffer(&iBuffer);
		graphics->get3Ddevice()->SetStreamSource(0, vBuffer, 0, sizeof(LVertex));
		graphics->get3Ddevice()->SetIndices(iBuffer);
		D3DXMatrixScaling(&scaleMat, this->scale.x, this->scale.y, this->scale.z);
		D3DXMatrixTranslation(&transMat, this->pos.x, this->pos.y, this->pos.z);
		worldMat = scaleMat * transMat;
		graphics->get3Ddevice()->SetTransform(D3DTS_WORLD, &worldMat);
		this->meshPtr->DrawSubset(0);
	}	
}

GUIBar::~GUIBar() {

}
