#pragma once
#include <SDL.h>
#include <string>
#include "GameScreen.h"
#include "UnitFactory.h"
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
	void ReadFile(string);
private:
	static GameScreen* currentScreen;
	static SDL_Renderer * renderer;
	static UnitFactory* unitFactory;
	static LTexture* imagesSpriteSheet;

	bool isRunning;
	SDL_Window * window;
	SDL_Rect backgroundRect;
	static Game* instance;
	Game();
	int width; int height;
	float angle;
	int health;
	int oxygen;
	int fuel;
	int weapon;
	int weaponDelay;
	int weaponAmmo;
	int ammo;
	int CurrentClipIndex;

};
