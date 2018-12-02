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
	LTexture* OxygenEasterEggTexture;
	LTexture* FuelEasterEggTexture;
	LTexture* HealthEasterEggTexture;
	LTexture* WeaponEasterEggTexture;
	//Clips
	SDL_Rect explosionSpriteClips[20];
	SDL_Rect healthSpriteClip;
	SDL_Rect oxygenSpriteClip;
	SDL_Rect fuelSpriteClip;
	SDL_Rect FuelEasterEggClip;
	SDL_Rect OxygenEasterEggClip;
	SDL_Rect HealthEasterEggClip;
	SDL_Rect WeaponEasterEggClip;
	SDL_Rect AsteroidClip;
	SDL_Rect pauseScreenSpriteClip;
	SDL_Rect enemyHealthBoundary;
	SDL_Rect heroHealthBoundary;
	SDL_Rect heroOxygenBoundary;
	SDL_Rect heroFuelBoundary;
	//Queues
	Queue planets;
	Queue PlayerBulletQueue;
	Queue EnemyBulletQueue;
	Queue AsteroidQueue;
	Queue EasterEggQueue;
	//Buttons
	Button* ResumeGameBtn;
	Button* saveGameBtn;
	Button* backBtn;
	Button* quitGameBtn;
	//Titles
	Word* WeaponTitle;
	Word* AmmoCount;
	Word* PauseTitle;
	UnitFactory* unitFactory;
	Unit* wormHole;
	SDL_Renderer* renderer;
	Player* hero;
	Enemy* enemy;
	Orbs** ball;

public:
	BattleScreen();
	BattleScreen(SDL_Renderer* renderer, UnitFactory* unitFactory, LTexture* imagesSpriteSheet, bool comingFromMenu = false);
	BattleScreen(SDL_Renderer* renderer, UnitFactory* unitFactory, LTexture* imagesSpriteSheet, const char* savedFileName);
	~BattleScreen();
	void Render();
	bool IsEmpty(string);
	void WriteFile(string);
	void HandleEvents(SDL_Event&);
};
