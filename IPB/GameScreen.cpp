#include "pch.h"
#include "GameScreen.h"

void GameScreen::setUnitFactory(UnitFactory * unitFactory)
{
	this->unitFactory = unitFactory;
}

void GameScreen::setImagesSpriteSheet(LTexture * imagesSpriteSheet)
{
	this->imagesSpriteSheet = imagesSpriteSheet;
}
