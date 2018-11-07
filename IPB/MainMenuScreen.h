#pragma once
#include "GameScreen.h"
#include "LTexture.h"
#include "Button.h"

class MainMenuScreen : public GameScreen
{
private:
	LTexture* logoTexture;
	Button* startGameBtn;
	Button* loadGameBtn;
	Button* selectLevelBtn;
	Button* quitGameBtn;
public:
	MainMenuScreen();
	~MainMenuScreen();
	void render();
	void handleEvents(SDL_Event&);
};