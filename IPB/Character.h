#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include"LTexture.h"
#include"Point.h"

class Character
{
public:
	Character();
	~Character();
	Character(char c, LTexture * gSpriteSheetTexture);
	void render(SDL_Renderer * gRenderer);
	void setPosition(int x, int y);
	void setChar(char c);
	void setTexture(LTexture * gSpriteSheetTexture, char c);
private:
	int x, y;
	SDL_Rect charRect;
	char shownChar;
	LTexture * CharTexture;
};