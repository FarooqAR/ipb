#pragma once
#include "constants.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include "GameScreen.h"
#include "UnitFactory.h"
#include "LTexture.h"
#include <string>

class Game
{
public:
	~Game();
	static Game * getInstance();
	static void setCurrentScreen(int, const char* savedFilename = "");
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void PlayMusic(int MUSIC_TYPE);
	void StopMusic(int channel = -1);
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
	Mix_Chunk* themeChunk;
	Mix_Chunk* bulletChunk;
	Mix_Chunk* explosionChunk;
	Mix_Chunk* btnHoverChunk;
	Mix_Chunk* btnClickChunk;
	static Game* instance;
	Game();
};

