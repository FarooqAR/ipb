#pragma once
#include <SDL.h>
#include "GameScreen.h"
#include "LTexture.h"
#include "Word.h"
#include "Button.h"

class PauseScreen : public GameScreen
{
private:
	LTexture* alphabetsSpriteSheet;
	LTexture* buttonSpriteSheet;

	Button* ResumeGameBtn;
	Button* saveGameBtn;
	Button* backBtn;
	Button* quitGameBtn;
	SDL_Renderer* renderer;
	Word* gameTitle;
public:
	PauseScreen(SDL_Renderer*);
	~PauseScreen();
	void render();
	void handleEvents(SDL_Event&);
	Word* setWordPosition(int x, int y);
};