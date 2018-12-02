#pragma once
#include <SDL.h>
#include <string>
#include "GameScreen.h"
#include "UnitFactory.h"
#include "LTexture.h"
#include "constants.h"
#include <string>

class Game
{
public:
	~Game();
	static Game * getInstance();
	static void setCurrentScreen(int, const char* savedFilename = "");
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running();
private:
	static GameScreen* currentScreen;
	static SDL_Renderer * renderer;
	static UnitFactory* unitFactory;
	static LTexture* imagesSpriteSheet;
	static bool isFirstTimer;

	bool isRunning;
	SDL_Window * window;
	SDL_Rect backgroundRect;
	static Game* instance;
	Game();
};

