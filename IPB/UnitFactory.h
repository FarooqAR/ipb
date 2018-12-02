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
	Attractor * createPlanet(LTexture*, int, int, int, float);
	Asteroid * createAsteroid(LTexture*,  int scale);
	EasterEgg * createEasterEgg(LTexture*, int EggType);
};