#include "VertexShape.h"


VertexShape::VertexShape() {
}


VertexShape::~VertexShape() {
}

void VertexShape::init(Game* gamePtr) {

}

void VertexShape::draw(float deltaTime) {
	graphics->get3Ddevice()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
}

void VertexShape::update(float deltaTime) {

}