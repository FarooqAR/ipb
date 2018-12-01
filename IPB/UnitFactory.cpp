#include "pch.h"
#include "UnitFactory.h"
#include "constants.h"
#include "Attractor.h"
#include "LTexture.h"

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

Attractor * UnitFactory::createPlanet(LTexture* imageSpriteSheet, int planetType, int x, int y, float scale)
{
	return new Attractor(gRenderer, imageSpriteSheet, planetType, x, y, scale);
}
