#pragma once
#include "GameScreen.h"
#include "Level.h"
#include "Button.h"

class SelectLevelScreen :GameScreen
{
public:
	SelectLevelScreen();
	~SelectLevelScreen();
	void selectLevel();
	void handleEvents(SDL_Event&);
	void render();

private:
	Button* selectLevelBtns;
	Level* levels;
	Level* selectedLevel;
};
