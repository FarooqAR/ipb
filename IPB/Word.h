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
	void Render(SDL_Renderer * gRenderer);
	void SetText(string str);
	void SetPosition(int x, int y);
	void SetXCentered();
	void SetYCentered();
	int GetTextLength();
	int GetX();
	int GetY();
private:
	Point position;
	int charSpacing;
	float scale = 1;
	string renderWord;
	LTexture * txtTexture;
	Character * characters;
};