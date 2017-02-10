#include "VertexShape.h"


VertexShape::VertexShape() {
	static int id_ = 0;
	this->id = id_++;
	meshPtr = nullptr;
	spawntime = timeGetTime();
	vertices = 0;
	indices = 0;
}

VertexShape::~VertexShape() {
}

void VertexShape::init(Audio* audio, Graphics* graphics, Input* input) {
	this->audio = audio;			// The audio system
	this->graphics = graphics;
	this->input = input;
}

void VertexShape::draw(D3DXMATRIX& worldMat) {
}

void VertexShape::update(float deltaTime) {

}

bool VertexShape::outOfMap() {

	D3DXVECTOR2 out;
	graphics->camera->pointOnScreen(out, pos);
	if (out.x > graphics->camera->vp.Width || out.x < 0 || out.y > graphics->camera->vp.Height || out.y < 0) {
		return true;
	}
	return false;

}