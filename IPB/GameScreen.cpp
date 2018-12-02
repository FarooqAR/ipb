#include "pch.h"
#include "GameScreen.h"

void GameScreen::SetUnitFactory(UnitFactory * unitFactory)
{
	this->unitFactory = unitFactory;
}

void GameScreen::SetImagesSpriteSheet(LTexture * imagesSpriteSheet)
{
	this->imagesSpriteSheet = imagesSpriteSheet;
}
