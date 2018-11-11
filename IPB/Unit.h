#pragma once
#include "Game.h"
#include "Point.h"
#include "LTexture.h"

class Unit
{
public:
	Unit(const char* textureSheet, SDL_Renderer* ren, int x, int y);
	Unit();
	~Unit();
	void setPos(int x, int y);
	void setAngle(double);
	void update();
	void render();
	Point getPos(); 
	double getAngle();

protected:
	Point pos;
	double angle;
	LTexture * objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;

};
