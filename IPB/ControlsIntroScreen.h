#pragma once
#include "GameScreen.h"
#include "Button.h"
#include "Word.h"

class ControlsIntroScreen : public GameScreen
{
public:
	ControlsIntroScreen(SDL_Renderer*, LTexture* imagesSpriteSheet);
	~ControlsIntroScreen();
	void render();
	void handleEvents(SDL_Event&);

private:
	Button* upBtn;
	Button* leftBtn;
	Button* rightBtn;
	Button* goBtn;
	Word* title;
	Word* thrustLabel;
	Word* turnRightLabel;
	Word* turnLeftLabel;
	SDL_Renderer* renderer;
};

