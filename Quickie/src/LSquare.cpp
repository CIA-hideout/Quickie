#include "LSquare.h"

LSquare::LSquare() : VertexShape() {
}


LSquare::~LSquare() {
}

void LSquare::init(Game* gamePtr) {

	LVertex v_[] = {
		{ -1.0f, -1.0f, 20.0f, D3DCOLOR_XRGB(255, 255, 255), },
		{ -1.0f, 1.0f, 20.0f, D3DCOLOR_XRGB(255, 255, 255), },
		{ 1.0f, 1.0f, 20.0f, D3DCOLOR_XRGB(255, 255, 255), },
		{ 1.0f, -1.0f, 20.0f, D3DCOLOR_XRGB(255, 255, 255), },
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

void LSquare::draw() {

	graphics->get3Ddevice()->SetStreamSource(0, vertexBuffer, 0, sizeof(LVertex));
	graphics->get3Ddevice()->SetIndices(indexBuffer);
	graphics->get3Ddevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

}

void LSquare::update(float deltaTime) {

}