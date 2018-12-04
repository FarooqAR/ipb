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
	Weapon * CreateWeapon(int delay, int weaponType, int ammo);
	Bullet * CreateBullet(LTexture* imagesSpriteSheet, int weaponType, int x, int y, double angle);
	Asteroid * CreateAsteroid(LTexture*,  float scale);
	EasterEgg * CreateEasterEgg(LTexture*, int eggType);
};