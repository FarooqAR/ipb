#pragma once
#include "UnitFactory.h"
#include "GameScreen.h"
#include "LTexture.h"
#include "Player.h"
#include "Attractor.h"
#include "EasterEgg.h"
#include "Asteroid.h"
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
	int astrExplosionSpriteIndex;
	bool isPaused;
	bool isMoving;
	bool intoWormHole;

	//Textures
	LTexture* AsteroidTexture;
	LTexture* explosionTexture;
	LTexture* bulletTexture;
	LTexture* healthBarTexture;
	LTexture* oxygenBarTexture;
	LTexture* fuelBarTexture;
	LTexture* destinationTexture;
	LTexture* wormHoleTexture;
	LTexture* fadeScreenTexture;
	LTexture* oxygenEasterEggTexture;
	LTexture* fuelEasterEggTexture;
	LTexture* healthEasterEggTexture;
	LTexture* weaponEasterEggTexture;
	//Clips
	SDL_Rect explosionSpriteClips[20];
	SDL_Rect healthSpriteClip;
	SDL_Rect oxygenSpriteClip;
	SDL_Rect fuelSpriteClip;
	SDL_Rect fuelEasterEggClip;
	SDL_Rect oxygenEasterEggClip;
	SDL_Rect healthEasterEggClip;
	SDL_Rect weaponEasterEggClip;
	SDL_Rect asteroidClip;
	SDL_Rect pauseScreenSpriteClip;
	SDL_Rect enemyHealthBoundary;
	SDL_Rect heroHealthBoundary;
	SDL_Rect heroOxygenBoundary;
	SDL_Rect heroFuelBoundary;
	Player* hero;
	Enemy* enemy;
	Orbs** ball;
	Queue planets;
	Queue playerBulletQueue;
	Queue enemyBulletQueue;
	Queue asteroidQueue;
	Queue easterEggQueue;
	//Buttons
	Button* resumeGameBtn;
	Button* saveGameBtn;
	Button* backBtn;
	Button* quitGameBtn;
	UnitFactory* unitFactory;
	Unit* wormHole;
	SDL_Renderer* renderer;
	Word* weaponTitle;
	Word* ammoCount;
	Word* pauseTitle;
	string s;

public:
	BattleScreen(SDL_Renderer* renderer, UnitFactory* unitFactory, LTexture* imagesSpriteSheet);
	BattleScreen(SDL_Renderer* renderer, UnitFactory* unitFactory, LTexture* imagesSpriteSheet, const char* savedFileName);
	~BattleScreen();
	void Render();
	void RenderWormHole();
	void RenderStatusBars();
	void RenderRandomEasterEggs();
	void RenderPlayer();
	void RenderEnemy();
	void RenderFadeScreen();
	void ShootEnemyBullet();
	bool IsEmpty(string);
	void WriteFile(string);
	void HandleEvents(SDL_Event&);
};
