#pragma once
#include <SDL.h>
class GameScreen
{
public:	
	//virtual ~GameScreen() = 0;
	virtual void render() = 0;
	virtual void handleEvents(SDL_Event&) = 0;
};
