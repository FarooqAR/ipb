#pragma once
#include "GameScreen.h"
#include "LTexture.h"
#include "Player.h"
#include "Attractor.h"
#include "EasterEgg.h"
#include "Level.h"
#include "Queue.h" 
#include "Unit.h"

class BattleScreen: public GameScreen 
{
private:
	int frames;
	int explosionSpriteIndex;
	LTexture* backgroundTexture;
	LTexture* explosionTexture;
	LTexture* healthBarTexture;
	LTexture* oxygenBarTexture;
	LTexture* fuelBarTexture;
	LTexture* destinationTexture;
	SDL_Renderer* renderer;
	SDL_Rect explosionSpriteClips[20];
	Player* hero;
	Level* currentLevel;
	Queue planets;

public:
	BattleScreen(SDL_Renderer* renderer);
	~BattleScreen();
	void render();
	void handleEvents(SDL_Event&);
};

