
#pragma once
#include <SDL.h>
#include "GameScreen.h"
#include "Level.h"
#include "Button.h"
#include "LTexture.h"
#include "Word.h"



class SelectLevelScreen : public GameScreen
{
public:
	SelectLevelScreen(SDL_Renderer*, LTexture* imagesSpriteSheet);
	~SelectLevelScreen();
	void selectLevel();
	void handleEvents(SDL_Event&);
	void render();
	Word* setWordPosition(int x, int y);


private:
	Button* selectLevelBtns;
	Level* levels;
	Level* selectedLevel;
	SDL_Renderer* renderer;
	Word* ScreenTitle;

	Button* lvl1;
	Button* lvl2;
	Button* lvl3;
	Button* lvl4;
	Button* BackBtn;
};

