#pragma once
#include <SDL.h>
#include "GameScreen.h"
#include "LTexture.h"
#include "Word.h"
#include "Button.h"

class SplashScreen : public GameScreen
{
private:
	LTexture* imagesSpriteSheet;
	int frames;
	SDL_Renderer* renderer;
	Word* gameTitle;
	Word* subTitle;
public:
	SplashScreen(SDL_Renderer*, LTexture* imagesSpriteSheet);
	~SplashScreen();
	void render();
	void handleEvents(SDL_Event&);
};
