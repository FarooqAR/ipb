#pragma once
#include <SDL.h>
#include "GameScreen.h"
#include "Button.h"
#include "LTexture.h"
#include "Word.h"

class LoadGameScreen : public GameScreen
{
private:
	LTexture* alphabetsSpriteSheet;
	LTexture* buttonSpriteSheet;

	Button* selectSaved1Btn; 
	Button* selectSaved2Btn;
	Button* selectSaved3Btn;
	Button* backBtn;
	SDL_Renderer* renderer;
	Word* ScreenTitle;
	Word* SubTitle;
public:
	LoadGameScreen(SDL_Renderer*);
	~LoadGameScreen();
	void handleEvents(SDL_Event&);
	void startSavedGameFromFile(const char *);
	void render();
	Word* setWordPosition(int x, int y);
};