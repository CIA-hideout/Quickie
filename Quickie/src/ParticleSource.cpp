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
}

ParticleSource::~ParticleSource() {
}

void ParticleSource::init(Graphics* graphics) {
	std::random_device rdev;
	std::mt19937 generator(rdev());
	std::uniform_real_distribution<float> distribution(-5.0f, 5.0f);

	this->graphics = graphics;

	// create the particles here

	for (int i = 0; i < particleCount; i++) {
		VertexShape* vs = new VertexShape();

		vs->graphics = graphics;

		D3DXCreateMeshFVF(12, 24, D3DXMESH_MANAGED, CUSTOMFVF, graphics->get3Ddevice(), &vs->meshPtr);

		vs->color = color;

		vs->objectType = OBJECT_TYPE_PARTICLE;

		vs->meshPtr->LockVertexBuffer(0, (void**)&vs->vertices);

		// 0
		vs->vertices[0] = { -0.5f / ASPECT_RATIO / 2, -0.5f / 2, -0.5f / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(vs->color.x), (int)(vs->color.y), (int)(vs->color.z)) };
		// 1
		vs->vertices[1] = { -0.5f / ASPECT_RATIO / 2, +0.5f / 2, -0.5f / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(vs->color.x), (int)(vs->color.y), (int)(vs->color.z)) };
		// 2
		vs->vertices[2] = { +0.5f / ASPECT_RATIO / 2, +0.5f / 2, -0.5f / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(vs->color.x), (int)(vs->color.y), (int)(vs->color.z)) };
		// 3
		vs->vertices[3] = { +0.5f / ASPECT_RATIO / 2, -0.5f / 2, -0.5f / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(vs->color.x), (int)(vs->color.y), (int)(vs->color.z)) };
		// 4
		vs->vertices[4] = { -0.5f / ASPECT_RATIO / 2, -0.5f / 2, +0.5f / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(vs->color.x), (int)(vs->color.y), (int)(vs->color.z)) };
		// 5
		vs->vertices[5] = { -0.5f / ASPECT_RATIO / 2, +0.5f / 2, +0.5f / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(vs->color.x), (int)(vs->color.y), (int)(vs->color.z)) };
		// 6
		vs->vertices[6] = { +0.5f / ASPECT_RATIO / 2, +0.5f / 2, +0.5f / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(vs->color.x), (int)(vs->color.y), (int)(vs->color.z)) };
		// 7
		vs->vertices[7] = { +0.5f / ASPECT_RATIO / 2, -0.5f / 2, +0.5f / ASPECT_RATIO / 2, D3DCOLOR_XRGB((int)(vs->color.x), (int)(vs->color.y), (int)(vs->color.z)) };

		vs->meshPtr->UnlockVertexBuffer();

		vs->vertexCount = 8;

		vs->meshPtr->LockIndexBuffer(0, (void**)&vs->indices);

		vs->indices[0] = 0; vs->indices[1] = 1; vs->indices[2] = 2;
		vs->indices[3] = 0; vs->indices[4] = 2; vs->indices[5] = 3;
		// back
		vs->indices[6] = 4; vs->indices[7] = 6; vs->indices[8] = 5;
		vs->indices[9] = 4; vs->indices[10] = 7; vs->indices[11] = 6;
		// left
		vs->indices[12] = 4; vs->indices[13] = 5; vs->indices[14] = 1;
		vs->indices[15] = 4; vs->indices[16] = 1; vs->indices[17] = 0;
		// right
		vs->indices[18] = 3; vs->indices[19] = 2; vs->indices[20] = 6;
		vs->indices[21] = 3; vs->indices[22] = 6; vs->indices[23] = 7;
		// top
		vs->indices[24] = 1; vs->indices[25] = 5; vs->indices[26] = 6;
		vs->indices[27] = 1; vs->indices[28] = 6; vs->indices[29] = 2;
		// bottom
		vs->indices[30] = 4; vs->indices[31] = 0; vs->indices[32] = 3;
		vs->indices[33] = 4; vs->indices[34] = 3; vs->indices[35] = 7;

		vs->meshPtr->UnlockIndexBuffer();

		vs->indicesCount = 36;

		vs->visible = true;
		vs->alive = true;

		float v_;

		v_ = distribution(generator) / 5.0f;
		distribution = std::uniform_real_distribution<float>(0, 2 * D3DX_PI);

		rotation.z = distribution(generator);

		if (this->inherit) {
			vs->velocity.x = (v_ * cos(rotation.z) + velocity.x * 15) / ASPECT_RATIO;
			vs->velocity.y = v_ * sin(rotation.z) + velocity.y * 15;
			vs->velocity.z = distribution(generator) / 5.0f + velocity.z * 15;
		}
		else {
			vs->velocity.x = (v_ * cos(rotation.z))/ ASPECT_RATIO;
			vs->velocity.y = v_ * sin(rotation.z);
			vs->velocity.z = distribution(generator) / 5.0f;
		}
		
		vs->pos = pos;

		particles.push_back(vs);
	}
}

void ParticleSource::draw(D3DXMATRIX& worldMat) {

	LPDIRECT3DVERTEXBUFFER9 vBuffer;
	LPDIRECT3DINDEXBUFFER9 iBuffer;

	for (int i = 0; i < particleCount; i++) {
		particles[i]->meshPtr->GetVertexBuffer(&vBuffer);
		particles[i]->meshPtr->GetIndexBuffer(&iBuffer);
		particles[i]->graphics->get3Ddevice()->SetStreamSource(0, vBuffer, 0, sizeof(LVertex));
		particles[i]->graphics->get3Ddevice()->SetIndices(iBuffer);
		D3DXMatrixTranslation(&worldMat, particles[i]->pos.x, particles[i]->pos.y, particles[i]->pos.z);
		particles[i]->graphics->get3Ddevice()->SetTransform(D3DTS_WORLD, &worldMat);
		particles[i]->meshPtr->DrawSubset(0);
	}
}

void ParticleSource::update(float deltaTime, std::vector<VertexShape*>& vS) {
	for (int i = 0; i < particleCount; i++) {
		particles[i]->velocity *= 0.95f;
	}
	move(vS, deltaTime);
}

void ParticleSource::move(std::vector<VertexShape*>& vS, float deltaTime) {

	printf("moving\n");

	for (int i = 0; i < particleCount; i++) {
		particles[i]->pos.x += particles[i]->velocity.x;
		//for (int j = 0; j < vS.size(); j++) {
		//	if (vS[j]->objectType == OBJECT_TYPE_OBSTACLE) {
		//		if (CollisionManager::collideAABB(particles[i], vS[j])) {
		//			if (particles[i]->velocity.x > 0)
		//				particles[i]->pos.x = vS[j]->min.x + (particles[i]->min.x - particles[i]->max.x) / 2 - 0.0001;
		//			else if (particles[i]->velocity.x < 0)
		//				particles[i]->pos.x = vS[j]->max.x - (particles[i]->min.x - particles[i]->max.x) / 2 + 0.0001;
		//			particles[i]->velocity.x = 0;
		//		}
		//	}
		//}

		particles[i]->pos.y += particles[i]->velocity.y;
		//for (int j = 0; j < vS.size(); j++) {
		//	if (vS[j]->objectType == OBJECT_TYPE_OBSTACLE) {
		//		if (CollisionManager::collideAABB(particles[i], vS[j])) {
		//			if (particles[i]->velocity.y > 0)
		//				particles[i]->pos.y = vS[j]->min.y + (particles[i]->min.y - particles[i]->max.y) / 2 - 0.0001;
		//			else if (particles[i]->velocity.y < 0)
		//				particles[i]->pos.y = vS[j]->max.y - (particles[i]->min.y - particles[i]->max.y) / 2 + 0.0001;
		//			particles[i]->velocity.y = 0;
		//		}
		//	}
		//}
	}
}

void ParticleSource::clean() {
	for (int i = 0; i < particleCount; i++) {
		delete particles[i];
		particles[i] = nullptr;
	}

	particles.clear();
}