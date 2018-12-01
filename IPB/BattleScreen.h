#pragma once
#include "UnitFactory.h"
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
#include <fstream>
#include "orbs.h"


class BattleScreen: public GameScreen 
{
private:
	int frames;
	int heroExplosionSpriteIndex;
	int enemExplosionSpriteIndex;
	int level;
	bool isPaused;
	bool isMoving;
	bool intoWormHole;
	LTexture* explosionTexture;
	LTexture* bulletTexture;
	LTexture* healthBarTexture;
	LTexture* oxygenBarTexture;
	LTexture* fuelBarTexture;
	LTexture* destinationTexture;
	LTexture* wormHoleTexture;
	Unit* wormHole;
	LTexture* fadeScreenTexture;
	Word* WeaponTitle;
	Word* AmmoCount;
	SDL_Renderer* renderer;
	SDL_Rect explosionSpriteClips[20];
	SDL_Rect healthSpriteClip;
	SDL_Rect oxygenSpriteClip;
	SDL_Rect fuelSpriteClip;
	SDL_Rect pauseScreenSpriteClip;
	SDL_Rect enemyHealthBoundary;
	SDL_Rect heroHealthBoundary;
	SDL_Rect heroOxygenBoundary;
	SDL_Rect heroFuelBoundary;
	Player* hero;
	Enemy* enemy;
	orbs** ball;
	Level* currentLevel;
	Queue planets;
	Queue PlayerBulletQueue;
	Queue EnemyBulletQueue;
	Button* ResumeGameBtn;
	Button* saveGameBtn;
	Button* backBtn;
	Button* quitGameBtn;
	Word* PauseTitle;
	string s;

public:
	int ok = 1;
	BattleScreen();
	BattleScreen(SDL_Renderer* renderer, UnitFactory* unitFactory, LTexture* imagesSpriteSheet);
	BattleScreen(SDL_Renderer* renderer, UnitFactory* unitFactory, LTexture* imagesSpriteSheet, const char* savedFileName);
	~BattleScreen();
	void render();
	void handleEvents(SDL_Event&);

};
