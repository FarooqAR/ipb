#pragma once
#include <SDL.h>
#include "GameScreen.h"
#include "LTexture.h"
#include "Word.h"
#include "Button.h"

class PauseScreen : public GameScreen
{
private:
	Button* ResumeGameBtn;
	Button* saveGameBtn;
	Button* backBtn;
	Button* quitGameBtn;
	SDL_Renderer* renderer;
	Word* gameTitle;
public:
	PauseScreen(SDL_Renderer*, LTexture*);
	~PauseScreen();
	void Render();
	void HandleEvents(SDL_Event&);
};