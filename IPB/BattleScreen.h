#pragma once
#include "GameScreen.h"
#include "LTexture.h"
#include "Player.h"
#include "Attractor.h"
#include "EasterEgg.h"
#include "Level.h"
#include "Queue.h" 
#include "Unit.h"
#include "Word.h"
#include "Enemy.h"

class BattleScreen: public GameScreen 
{
private:
	int frames;
	int heroExplosionSpriteIndex;
	int enemExplosionSpriteIndex;
	LTexture* backgroundTexture;
	LTexture* explosionTexture;
	LTexture* bulletTexture;
	LTexture* healthBarTexture;
	LTexture* oxygenBarTexture;
	LTexture* fuelBarTexture;
	LTexture* destinationTexture;
	LTexture* alphabetsSpriteSheet;
	Word* WeaponTitle;
	Word* AmmoCount;
	SDL_Renderer* renderer;
	SDL_Rect explosionSpriteClips[20];
	Player* hero;
	Enemy* enemy;
	Level* currentLevel;
	Queue planets;
	Queue PlayerBulletQueue;
	Queue EnemyBulletQueue;

public:
	BattleScreen(SDL_Renderer* renderer);
	~BattleScreen();
	void render();
	void handleEvents(SDL_Event&);
};
