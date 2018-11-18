#pragma once
#include <SDL.h>
#include "GameScreen.h"
#include "LTexture.h"
#include "Word.h"
#include "Button.h"

class GameOverScreen : public GameScreen
{
private:
	LTexture* alphabetsSpriteSheet;
	LTexture* buttonSpriteSheet;

	Button* mainMenuBtn;
	Button* quitBtn;
	SDL_Renderer* renderer;
	Word* gameOverTitle;
public:
	GameOverScreen(SDL_Renderer*);
	~GameOverScreen();
	void render();
	void handleEvents(SDL_Event&);
	Word* setWordPosition(int x, int y);
};