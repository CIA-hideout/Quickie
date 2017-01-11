#include "LTriangle.h"

LTriangle::LTriangle() {

}


LTriangle::~LTriangle() {

}

void LTriangle::init(Game* gamePtr) {
	
	LVertex v_[] = {
		{ 2.5f, -2.0f, 1.0f, D3DCOLOR_XRGB(255, 255, 255), },
		{ 0.0f, 2.0f, 1.0f, D3DCOLOR_XRGB(255, 255, 255), },
		{ -2.5f, -2.0f, 1.0f, D3DCOLOR_XRGB(255, 255, 255), },
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

	D3DXMATRIX matRotate;

	static float index = 0.0f;
	index += 0.05f;

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
	graphics->get3Ddevice()->SetStreamSource(0, graphics->pVertexBuffer, 0, sizeof(LVertex));
	// graphics->get3Ddevice()->DrawPrimitive(D3DPT_LINELIST, 0, 1);
	graphics->get3Ddevice()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
}

void LTriangle::update(float deltaTime) {

}
