#pragma once
#include "GameScreen.h"
#include "LTexture.h"
#include "Player.h"
#include "Attractor.h"
#include "EasterEgg.h"
#include "Level.h"


class BattleScreen: public GameScreen 
{
private:
	LTexture* backgroundTexture;
	LTexture* healthBarSpriteTexture;
	LTexture* oxygenBarSpriteTexture;
	LTexture* fuelBarSpriteTexture;
	LTexture* destinationTexture;
	SDL_Renderer* renderer;
	Player* hero;
	Level* currentLevel;

public:
	BattleScreen(SDL_Renderer* renderer);
	~BattleScreen();
	void render();
	void handleEvents(SDL_Event&);
};

