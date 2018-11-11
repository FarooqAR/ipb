#pragma once
#include <SDL.h>
#include "GameScreen.h"
#include "LTexture.h"

class Game
{
public:
	~Game();
	static Game * getInstance();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running();
private:
	bool isRunning;
	SDL_Window * window;
	SDL_Renderer * renderer;
	GameScreen* currentScreen;
	LTexture* backgroundTexture;
	static Game* instance;
	Game();
};
