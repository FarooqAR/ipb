#pragma once
#include "Game.h"
#include "Point.h"

class Unit
{
public:
	Unit(const char* textureSheet, SDL_Renderer* ren, int x, int y);
	Unit();
	void setPos(int x, int y);
	Point getPos();
	void update();
	void render();

private:
	Point pos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;

};
