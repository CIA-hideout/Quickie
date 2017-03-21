#pragma once

#include "Behaviour.h"

class Run : public Behaviour
{

public:

	Run();
	~Run();

	void initialize(NodeManager* nM) override;
	void act(std::vector<VertexShape*>& vS, AI* computer) override;
	void randBehaviour() override;
};
