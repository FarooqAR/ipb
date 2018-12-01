#pragma once
#include <stdio.h>
#include "LTexture.h"
#include "Character.h"
#include "Point.h"

class Word
{
public:
	Word(string str, LTexture * imagesSpriteSheet, int x, int y, float scale = 1);
	~Word();
	void render(SDL_Renderer * gRenderer);
	void setText(string str);
	void setPosition(int x, int y);
	void setXCentered();
	void setYCentered();
	int getTextLength();
	int getX();
	int getY();
private:
	Point position;
	int charSpacing;
	float scale = 1;
	string renderWord;
	LTexture * txtTexture;
	Character * characters;
};