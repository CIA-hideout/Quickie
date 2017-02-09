#include "ParticleSource.h"

ParticleSource::ParticleSource() : VertexShape() {
}

ParticleSource::ParticleSource(int count, D3DXVECTOR3& srcV, D3DXVECTOR3& srcPos, D3DXVECTOR3& color, bool inherit) : VertexShape() {
	pos = srcPos;
	particleCount = count;
	this->color = color;
	objectType = OBJECT_TYPE_PARTICLES;
	velocity = srcV;
	duration = 3.0f;
	this->inherit = inherit;
	particles = 0;
}

ParticleSource::~ParticleSource() {
}

void ParticleSource::init(Graphics* graphics) {

	std::random_device rdev;
	std::mt19937 generator(rdev());
	std::uniform_real_distribution<float> distribution(-5.0f, 5.0f);

	this->graphics = graphics;

	particles = (ParticleData*)std::malloc(sizeof(ParticleData)* particleCount);

	vShape = new VertexShape();

	vShape->graphics = graphics;
	D3DXCreateMeshFVF(12, 24, D3DXMESH_MANAGED, CUSTOMFVF, graphics->get3Ddevice(), &vShape->meshPtr);
	vShape->color = color;
	vShape->objectType = OBJECT_TYPE_PARTICLE;
	vShape->meshPtr->LockVertexBuffer(0, (void**)&vShape->vertices);

	// 0
	vShape->vertices[0] = { -0.5f / ASPECT_RATIO / 2, -0.5f / 2, -0.5f / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(vShape->color.x), (int)(vShape->color.y), (int)(vShape->color.z)) };
	// 1
	vShape->vertices[1] = { -0.5f / ASPECT_RATIO / 2, +0.5f / 2, -0.5f / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(vShape->color.x), (int)(vShape->color.y), (int)(vShape->color.z)) };
	// 2
	vShape->vertices[2] = { +0.5f / ASPECT_RATIO / 2, +0.5f / 2, -0.5f / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(vShape->color.x), (int)(vShape->color.y), (int)(vShape->color.z)) };
	// 3
	vShape->vertices[3] = { +0.5f / ASPECT_RATIO / 2, -0.5f / 2, -0.5f / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(vShape->color.x), (int)(vShape->color.y), (int)(vShape->color.z)) };
	// 4
	vShape->vertices[4] = { -0.5f / ASPECT_RATIO / 2, -0.5f / 2, +0.5f / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(vShape->color.x), (int)(vShape->color.y), (int)(vShape->color.z)) };
	// 5
	vShape->vertices[5] = { -0.5f / ASPECT_RATIO / 2, +0.5f / 2, +0.5f / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(vShape->color.x), (int)(vShape->color.y), (int)(vShape->color.z)) };
	// 6
	vShape->vertices[6] = { +0.5f / ASPECT_RATIO / 2, +0.5f / 2, +0.5f / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(vShape->color.x), (int)(vShape->color.y), (int)(vShape->color.z)) };
	// 7
	vShape->vertices[7] = { +0.5f / ASPECT_RATIO / 2, -0.5f / 2, +0.5f / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(vShape->color.x), (int)(vShape->color.y), (int)(vShape->color.z)) };

	vShape->meshPtr->UnlockVertexBuffer();
	vShape->vertexCount = 8;
	vShape->meshPtr->LockIndexBuffer(0, (void**)&vShape->indices);

	vShape->indices[0] = 0; vShape->indices[1] = 1; vShape->indices[2] = 2;
	vShape->indices[3] = 0; vShape->indices[4] = 2; vShape->indices[5] = 3;
	// back
	vShape->indices[6] = 4; vShape->indices[7] = 6; vShape->indices[8] = 5;
	vShape->indices[9] = 4; vShape->indices[10] = 7; vShape->indices[11] = 6;
	// left
	vShape->indices[12] = 4; vShape->indices[13] = 5; vShape->indices[14] = 1;
	vShape->indices[15] = 4; vShape->indices[16] = 1; vShape->indices[17] = 0;
	// right
	vShape->indices[18] = 3; vShape->indices[19] = 2; vShape->indices[20] = 6;
	vShape->indices[21] = 3; vShape->indices[22] = 6; vShape->indices[23] = 7;
	// top
	vShape->indices[24] = 1; vShape->indices[25] = 5; vShape->indices[26] = 6;
	vShape->indices[27] = 1; vShape->indices[28] = 6; vShape->indices[29] = 2;
	// bottom
	vShape->indices[30] = 4; vShape->indices[31] = 0; vShape->indices[32] = 3;
	vShape->indices[33] = 4; vShape->indices[34] = 3; vShape->indices[35] = 7;

	vShape->meshPtr->UnlockIndexBuffer();
	vShape->indicesCount = 36;
	vShape->visible = true;
	vShape->alive = true;

	float v_;

	distribution = std::uniform_real_distribution<float>(0, 2 * D3DX_PI);

	for (int i = 0; i < particleCount; i++)  {

		v_ = distribution(generator) / 5.0f;
		rotation.z = distribution(generator);

		if (this->inherit) {
			particles[i].velocity.x = (v_ * cos(rotation.z) + velocity.x * 15) / ASPECT_RATIO;
			particles[i].velocity.y = v_ * sin(rotation.z) + velocity.y * 15;
			particles[i].velocity.z = distribution(generator) / 5.0f + velocity.z * 15;
		}
		else {
			particles[i].velocity.x = (v_ * cos(rotation.z)) / ASPECT_RATIO;
			particles[i].velocity.y = v_ * sin(rotation.z);
			particles[i].velocity.z = distribution(generator) / 5.0f;
		}

		particles[i].pos = pos;

		// printf("particle %d, pos.x = %.2f, %.2f\n", i + 1, particles[i].pos.x, particles[i].pos.y);
	}

}

void ParticleSource::draw(D3DXMATRIX& worldMat) {

	LPDIRECT3DVERTEXBUFFER9 vBuffer;
	LPDIRECT3DINDEXBUFFER9 iBuffer;

	for (int i = 0; i < particleCount; i++) {
		vShape->meshPtr->GetVertexBuffer(&vBuffer);
		vShape->meshPtr->GetIndexBuffer(&iBuffer);
		vShape->graphics->get3Ddevice()->SetStreamSource(0, vBuffer, 0, sizeof(LVertex));
		vShape->graphics->get3Ddevice()->SetIndices(iBuffer);
		D3DXMatrixTranslation(&worldMat, particles[i].pos.x, particles[i].pos.y, particles[i].pos.z);
		vShape->graphics->get3Ddevice()->SetTransform(D3DTS_WORLD, &worldMat);
		vShape->meshPtr->DrawSubset(0);
	}
}

void ParticleSource::update(float deltaTime, std::vector<VertexShape*>& vS) {
	for (int i = 0; i < particleCount; i++) {
		particles[i].velocity *= 0.95f;
	}
	move(vS, deltaTime);
}

void ParticleSource::move(std::vector<VertexShape*>& vS, float deltaTime) {

	for (int i = 0; i < particleCount; i++) {
		particles[i].pos.x += particles[i].velocity.x;
		particles[i].pos.y += particles[i].velocity.y;
	}
}

void ParticleSource::clean() {
	for (int i = 0; i < particleCount; i++) {
		delete particles;
		particles = 0;
	}
}