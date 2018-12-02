#pragma once
#include <SDL.h>
#include "GameScreen.h"
#include "LTexture.h"
#include "Word.h"
#include "Button.h"

class MainMenuScreen : public GameScreen
{
private:
	LTexture* imagesSpriteSheet;

	Button* startGameBtn;
	Button* loadGameBtn;
	Button* selectLevelBtn;
	Button* quitGameBtn;
	SDL_Renderer* renderer;
	Word* gameTitle;
public:
	MainMenuScreen(SDL_Renderer*, LTexture* imagesSpriteSheet);
	~MainMenuScreen();
	void Render();
	void HandleEvents(SDL_Event&);
};