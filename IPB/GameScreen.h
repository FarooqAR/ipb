#pragma once
#include <SDL.h>
#include "UnitFactory.h"
#include "LTexture.h"
class GameScreen
{
protected:
	UnitFactory* unitFactory;
	LTexture* imagesSpriteSheet;
public:	
	virtual void render() = 0;
	virtual void handleEvents(SDL_Event&) = 0;
	void setUnitFactory(UnitFactory*);
	void setImagesSpriteSheet(LTexture*);
};
