#pragma once
#include "GameScreen.h"
#include "Button.h"

class MainMenuScreen : public GameScreen
{
private:
	Button* selectSavedGameBtns; 
public:
	MainMenuScreen();
	~MainMenuScreen();
	void startSavedGameFromFile(const char *);
	void render();
	void handleEvents(SDL_Event&);
};