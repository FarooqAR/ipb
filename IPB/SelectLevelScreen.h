
#pragma once
#include <SDL.h>
#include "GameScreen.h"
#include "Button.h"
#include "LTexture.h"
#include "Word.h"



class SelectLevelScreen : public GameScreen
{
public:
	SelectLevelScreen(SDL_Renderer*, LTexture* imagesSpriteSheet);
	~SelectLevelScreen();
	void HandleEvents(SDL_Event&);
	void Render();


private:
	SDL_Renderer* renderer;
	Word* screenTitle;

	Button* lvl1;
	Button* lvl2;
	Button* lvl3;
	Button* backBtn;
};

