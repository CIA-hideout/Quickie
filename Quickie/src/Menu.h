#pragma once

#include <stack>
#include "State.h"

class Menu : public State
{

public:
	Menu();
	virtual ~Menu();

	void initialize(Graphics* graphics, Input* input, Audio* audio, rapidjson::Document& doc, float* deltaTime) override;
	void update() override;
	void ai() override{};
	void render() override;
	void collisions() override{};
	void releaseAll() override{};
	void resetAll() override{};
};
