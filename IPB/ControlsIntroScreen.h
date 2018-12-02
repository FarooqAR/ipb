#pragma once
#include "GameScreen.h"
#include "Button.h"
#include "Word.h"

class ControlsIntroScreen : public GameScreen
{
public:
	ControlsIntroScreen(SDL_Renderer*, LTexture* imagesSpriteSheet);
	~ControlsIntroScreen();
	void Render();
	void HandleEvents(SDL_Event&);

private:
	Button* upBtn;
	Button* leftBtn;
	Button* rightBtn;
	Button* spaceBtn;
	Button* goBtn;
	Word* title;
	Word* thrustLabel;
	Word* turnRightLabel;
	Word* turnLeftLabel;
	Word* shootLabel;
	SDL_Renderer* renderer;
};

