#pragma once
#include <SDL.h>
#include <stdio.h> 
#include "LTexture.h"
#include "Word.h"
#include "Point.h"

class Button
{
public:
	Button();
	~Button();
	Button(LTexture * bgTexture, LTexture * alphabetsSpriteSheet, string label, int x, int y);
	void render(SDL_Renderer * gRenderer);
	void setPosition(int x, int y);
private:
	Word * label;
	Point position;
	LTexture * btnTexture;
	SDL_Rect spritRect;
};

