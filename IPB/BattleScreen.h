#pragma once
#include "UnitFactory.h"
#include "GameScreen.h"
#include "LTexture.h"
#include "Player.h"
#include "Attractor.h"
#include "EasterEgg.h"
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
	LTexture* explosionTexture;
	LTexture* bulletTexture;
	LTexture* healthBarTexture;
	LTexture* oxygenBarTexture;
	LTexture* fuelBarTexture;
	LTexture* destinationTexture;
	LTexture* wormHoleTexture;
	Unit* wormHole;
	LTexture* fadeScreenTexture;
	Word* weaponTitle;
	Word* ammoCount;
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
	Orbs** ball;
	Queue planets;
	Queue playerBulletQueue;
	Queue enemyBulletQueue;
	Button* resumeGameBtn;
	Button* saveGameBtn;
	Button* backBtn;
	Button* quitGameBtn;
	Word* pauseTitle;
	string s;

public:
	BattleScreen(SDL_Renderer* renderer, UnitFactory* unitFactory, LTexture* imagesSpriteSheet, bool comingFromMenu = false);
	BattleScreen(SDL_Renderer* renderer, UnitFactory* unitFactory, LTexture* imagesSpriteSheet, const char* savedFileName);
	~BattleScreen();
	void Render();
	bool IsEmpty(string);
	void WriteFile(string);
	void HandleEvents(SDL_Event&);
};
