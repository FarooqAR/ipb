#pragma once
#include "LTexture.h"
#include "Character.h"

class Word
{
public:
	~Word();
	Word(string str, LTexture * gSpriteSheetTexture, int x, int y);
	void render(SDL_Renderer * gRenderer);
	void setText(string str);
	void setPosition(int x, int y);
	int getTextLength();
private:
	int x, y;
	string renderWord;
	LTexture * TxtTexture;
	Character * characters;
};