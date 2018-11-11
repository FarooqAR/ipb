#pragma once
#include <SDL.h>
#include "GameScreen.h"
#include "LTexture.h"
#include "Word.h"
#include "Button.h"

class MainMenuScreen : public GameScreen
{
private:
	LTexture* alphabetsSpriteSheet;
	LTexture* buttonSpriteSheet;

	Button* startGameBtn;
	Button* loadGameBtn;
	Button* selectLevelBtn;
	Button* quitGameBtn;
	SDL_Renderer* renderer;
	Word* gameTitle;
	//Button* startGameBtn;
	//Button* loadGameBtn;
	//Button* selectLevelBtn;
	//Button* quitGameBtn;
public:
	MainMenuScreen(SDL_Renderer*);
	~MainMenuScreen();
	void render();
	void handleEvents(SDL_Event&);
	Word* setWordPosition(int x, int y);
};