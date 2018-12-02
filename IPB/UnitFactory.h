#pragma once
#include <SDL.h>
#include "constants.h"
#include "Unit.h"
#include "Weapon.h"
#include "Attractor.h"
#include "EasterEgg.h"
#include "Bullet.h"
#include "LTexture.h"

class UnitFactory
{
private:
	UnitFactory(SDL_Renderer*);
	static UnitFactory* instance;
	SDL_Renderer* gRenderer;
public:
	static UnitFactory * getInstance(SDL_Renderer*);
	Attractor * CreatePlanet(LTexture*, int, int, int, float);
	Weapon * CreateWeapon(int x, int y, int weaponType);
	Unit * CreateAsteroid(int x, int y, int asteroidType, int speed);
	EasterEgg * CreateEasterEgg(int x, int y, int easterEggType);
	Bullet * CreateBullet(int x, int y, int bulletType, int speed);
};