#pragma once
#include <SDL.h>
#include "GameScreen.h"
#include "LTexture.h"
#include "Word.h"
#include "Button.h"

class GameOverScreen : public GameScreen
{
private:
	Button* mainMenuBtn;
	Button* quitBtn;
	SDL_Renderer* renderer;
	Word* gameOverTitle;
public:
	GameOverScreen(SDL_Renderer*, LTexture* imagesSpriteSheet);
	~GameOverScreen();
	void Render();
	void HandleEvents(SDL_Event&);
};