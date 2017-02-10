#pragma once

#include "graphics.h"
#include "audio.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/document.h"
#include "Input.h"


enum ObjectType {
	OBJECT_TYPE_PLAYER,
	OBJECT_TYPE_OBSTACLE,
	OBJECT_TYPE_QLINE,
	OBJECT_TYPE_PARTICLE,
	OBJECT_TYPE_PARTICLES,
	OBJECT_TYPE_WALL,
	OBJECT_TYPE_GUI_BAR,
	OBJECT_TYPE_NODE
};

class VertexShape {

public:

	Graphics*				graphics;
	Input*					input;
	Audio*					audio;	// pointer to audio system

	LPDIRECT3DVERTEXBUFFER9	vertexBuffer;
	LPDIRECT3DINDEXBUFFER9	indexBuffer;
	int						vertexCount, indicesCount;

	ID3DXMesh*				meshPtr;

	D3DXVECTOR3				pos;
	D3DXVECTOR3				dimension;
	D3DXVECTOR3				scale;
	D3DXVECTOR3				color;
	D3DXVECTOR3				rotation;

	D3DXMATRIX				matTrans, matRot, matScale;

	LVertex*				vertices;
	WORD*					indices;

	D3DXVECTOR3*			center;
	D3DXVECTOR3				min;
	D3DXVECTOR3				max;
	D3DXVECTOR3				velocity;
	float					radius;

	float					mass;

	DWORD					spawntime;

	ObjectType				objectType;

	int						id, health, maxHealth;
	bool					visible, alive, initialized;

	D3DPRIMITIVETYPE		primitiveType;

public:

	VertexShape();
	virtual ~VertexShape();
	virtual void init(Audio*, Graphics*, Input*);
	virtual void draw(D3DXMATRIX&);
	virtual void update(float);

	bool outOfMap();

};
