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
	void Render(SDL_Renderer* gRenderer);
	void SetPosition(int x, int y);
	void SetChar(char c);
	void SetScale(float scale);
	void SetTexture(LTexture* alphabetsSpriteSheet);
	int GetWidth();
	int GetHeight();
	int GetX();
	int GetY();

private:
	Point position;
	int w, h;
	float scale = 1;
	SDL_Rect charRect;
	char showChar;
	LTexture* alphabetsSpriteSheet;

};