#pragma once
#include <SDL.h>
#include "GameScreen.h"
#include "LTexture.h"
#include "constants.h"

class Game
{
public:
	~Game();
	static Game * getInstance();
	static void setCurrentScreen(int);
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running();
private:
	static GameScreen* currentScreen;
	static SDL_Renderer * renderer;
	bool isRunning;
	SDL_Window * window;
	LTexture* backgroundTexture;
	static Game* instance;
	Game();
};
