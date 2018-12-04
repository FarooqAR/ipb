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
	static Game * GetInstance();
	UnitFactory * GetUnitFactory();
	void SetCurrentScreen(int, const char* savedFilename = nullptr);
	void Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void PlayMusic(int MUSIC_TYPE);
	void StopMusic(int channel = -1);
	void HandleEvents();
	void Update();
	void Render();
	void Clean();
	bool Running();
private:
	GameScreen* currentScreen;
	SDL_Renderer * renderer;
	UnitFactory* unitFactory;
	LTexture* imagesSpriteSheet;
	bool isFirstTimer;

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

