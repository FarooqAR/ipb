#pragma once
#include "GameScreen.h"
#include "LTexture.h"
#include "Player.h"
#include "Attractor.h"
#include "EasterEgg.h"
#include "Level.h"
#include "Queue.h" 
#include "Unit.h"
#include "Enemy.h"
#include "Button.h"
#include "Word.h"

class BattleScreen: public GameScreen 
{
private:
	int frames;
	int heroExplosionSpriteIndex;
	int enemExplosionSpriteIndex;
	bool intoWormHole;
	LTexture* backgroundTexture;
	LTexture* explosionTexture;
	LTexture* bulletTexture;
	LTexture* healthBarTexture;
	LTexture* oxygenBarTexture;
	LTexture* fuelBarTexture;
	LTexture* destinationTexture;
	LTexture* alphabetsSpriteSheet;
	LTexture* wormHoleTexture;
	Unit* wormHole;
	Word* WeaponTitle;
	Word* AmmoCount;
	SDL_Renderer* renderer;
	SDL_Rect explosionSpriteClips[20];
	SDL_Rect enemyHealthBoundary;
	SDL_Rect heroHealthBoundary;
	SDL_Rect heroOxygenBoundary;
	SDL_Rect heroFuelBoundary;
	Player* hero;
	Enemy* enemy;
	Level* currentLevel;
	Queue planets;
	Queue PlayerBulletQueue;
	Queue EnemyBulletQueue;
	string s;
	LTexture* buttonSpriteSheet;

public:
	int ok = 1;
	BattleScreen();
	BattleScreen(SDL_Renderer* renderer, int h = 490, int w = 500, float angle = 0);
	~BattleScreen();
	void render();
	void handleEvents(SDL_Event&);
};
