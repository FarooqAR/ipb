#pragma once
#include "GameScreen.h"
#include "Button.h"

class LoadGameScreen : public GameScreen
{
private:
	Button* selectSavedGameBtns; 
public:
	LoadGameScreen();
	~LoadGameScreen();
	void startSavedGameFromFile(const char *);
	void render();
	void handleEvents(SDL_Event&);
};