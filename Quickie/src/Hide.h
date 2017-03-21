#pragma once

#include "Behaviour.h"

class Hide : public Behaviour
{

public:

	Hide();
	~Hide();

	void initialize(NodeManager* nM) override;
	void act(std::vector<VertexShape*>& vS, AI* computer) override;
	void randBehaviour() override;
};
