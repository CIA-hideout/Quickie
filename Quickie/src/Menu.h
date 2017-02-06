#pragma once

#include <stack>
#include "State.h"

enum Scene
{
		PLAY,				// main menu;		when is it displayed
		CONTROLS,			//
		REVERT
};

namespace menuNS
{
	const std::string				options[] = { "Play!", "Controls" };
	const int						optionsLength = 2;

}

class Menu : public State
{
	bool					firstGame;
	std::stack<Scene>		menuStack;

	void setCurrentSceneByInput(Scene s, int);

public:
	Menu();
	virtual ~Menu();
	
	void initialize(Graphics* graphics, Input* input, Audio* audio, rapidjson::Document& doc) override;
	void update() override;
	void ai() override{};
	void render() override;
	void collisions() override{};
	void releaseAll() override{};
	void resetAll() override{};
};
