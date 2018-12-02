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
	virtual void Render() = 0;
	virtual void HandleEvents(SDL_Event&) = 0;
	void SetUnitFactory(UnitFactory*);
	void SetImagesSpriteSheet(LTexture*);
};
