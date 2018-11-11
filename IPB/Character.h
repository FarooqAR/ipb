#pragma once
#include <SDL.h>
#include "LTexture.h"
#include "Point.h"

class Character
{
public:
	Character();
	Character(char c, LTexture* alphabetsSpriteSheet);
	~Character();
	void render(SDL_Renderer* gRenderer);
	void setPosition(int x, int y);
	void setChar(char c);
	void setScale(float scale);
	void setTexture(LTexture* alphabetsSpriteSheet);
	int getWidth();
	int getHeight();
	int getX();
	int getY();

private:
	Point position;
	int w, h;
	float scale = 1;
	SDL_Rect charRect;
	char showChar;
	LTexture* alphabetsSpriteSheet;

};