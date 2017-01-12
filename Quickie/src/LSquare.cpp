#include "LSquare.h"

LSquare::LSquare() : VertexShape() {
}


LSquare::~LSquare() {
}

void LSquare::init(Game* gamePtr) {

	LVertex v_[] = {
		{ 1.0f, -1.0f, 1.0f, D3DCOLOR_XRGB(0, 255, 0), },
		{ 1.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 255), },
		{ -1.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(255, 255, 255), },
		{ -1.0f, -1.0f, 1.0f, D3DCOLOR_XRGB(255, 255, 255), },
	};

	short indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	graphics = gamePtr->getGraphics();

	graphics->get3Ddevice()->CreateVertexBuffer(
		4 * sizeof(LVertex),
		0,
		CUSTOMFVF,
		D3DPOOL_MANAGED,
		&vertexBuffer,
		NULL
		);

	VOID* pVoid;

	vertexBuffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, v_, sizeof(v_));
	vertexBuffer->Unlock();

	graphics->get3Ddevice()->CreateIndexBuffer(
		6 * sizeof(short),
		0,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&indexBuffer,
		NULL
		);

	indexBuffer->Lock(0, 0, (void**)&pVoid, 0);
	memcpy(pVoid, indices, sizeof(indices));
	indexBuffer->Unlock();

}

void LSquare::draw(float deltaTime) {
	D3DXMATRIX matRotate;

	static float index = 0.0f;
	index += 0.1f * deltaTime;

	printf("%.2f\n", index);

	D3DXMatrixRotationZ(&matRotate, index);
	graphics->get3Ddevice()->SetTransform(D3DTS_WORLD, &matRotate);

	D3DXMATRIX matView;

	D3DXMatrixLookAtLH(&matView,
		&D3DXVECTOR3(0.0f, 0.0f, 10.0f),
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	graphics->get3Ddevice()->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIX matProjection;

	D3DXMatrixPerspectiveFovLH(
		&matProjection,
		PI / 4,
		(FLOAT)1200 / (FLOAT)1000,
		1.0f,
		1000.0f);

	graphics->get3Ddevice()->SetTransform(D3DTS_PROJECTION, &matProjection);
	graphics->get3Ddevice()->SetStreamSource(0, vertexBuffer, 0, sizeof(LVertex));
	// graphics->get3Ddevice()->DrawPrimitive(D3DPT_LINELIST, 0, 1);
	graphics->get3Ddevice()->SetIndices(indexBuffer);
	graphics->get3Ddevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}

void LSquare::update(float deltaTime) {

}