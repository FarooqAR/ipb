#include "pch.h"
#include "UnitFactory.h"
#include "constants.h"
#include "Attractor.h"
#include "LTexture.h"
#include "EasterEgg.h"


UnitFactory* UnitFactory::instance = nullptr;
UnitFactory::UnitFactory(SDL_Renderer* gRenderer)
	:gRenderer(gRenderer)
{

}
UnitFactory * UnitFactory::getInstance(SDL_Renderer* gRenderer)
{
	if (instance == nullptr)
		instance = new UnitFactory(gRenderer);
	return instance;
}

Attractor * UnitFactory::CreatePlanet(LTexture* imageSpriteSheet, int planetType, int x, int y, float scale)
{
	return new Attractor(gRenderer, imageSpriteSheet, planetType, x, y, scale);
}


Asteroid * UnitFactory::createAsteroid(LTexture* imageSpriteSheet, int scale)
{
	return new Asteroid(gRenderer, imageSpriteSheet, scale);
}

EasterEgg * UnitFactory::createEasterEgg(LTexture * imageSpriteSheet, int EggType)
{
	return new EasterEgg(gRenderer, imageSpriteSheet, EggType);
}


