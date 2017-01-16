#include "LTriangle.h"

LTriangle::LTriangle() : VertexShape() {

}


LTriangle::~LTriangle() {

}

void LTriangle::init(Game* gamePtr) {
	
	LVertex v_[] = {
		//{ 2.5f, -2.0f, 1.0f, D3DCOLOR_XRGB(255, 255, 255), },
		//{ 0.0f, 2.0f, 1.0f, D3DCOLOR_XRGB(255, 255, 255), },
		//{ -2.5f, -2.0f, 1.0f, D3DCOLOR_XRGB(255, 255, 255), },

		{ 1.0f, -1.0f, 0.1f, D3DCOLOR_XRGB(255, 255, 255), },
		{ 1.0f, 1.0f, 0.1f, D3DCOLOR_XRGB(255, 255, 255), },
		{ -1.0f, -1.0f, 0.1f, D3DCOLOR_XRGB(255, 255, 255), },
	};

	graphics = gamePtr->getGraphics();

	graphics->get3Ddevice()->CreateVertexBuffer(
		3 * sizeof(LVertex),
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

}

void LTriangle::draw() {

}

void LTriangle::update(float deltaTime) {

}
