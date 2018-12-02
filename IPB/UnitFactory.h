#pragma once
#include <SDL.h>
#include "constants.h"
#include "Unit.h"
#include "Weapon.h"
#include "Attractor.h"
#include "Asteroid.h"
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
	Bullet * CreateBullet(int x, int y, int bulletType, int speed);
	Asteroid * createAsteroid(LTexture*,  int scale);
	EasterEgg * createEasterEgg(LTexture*, int EggType);
};