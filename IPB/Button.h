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
	void onHover(int clickX, int clickY);
	void onClickDown(int clickX, int clickY);
	bool onClickUp(int clickX, int clickY);
	Button(LTexture * bgTexture, LTexture * alphabetsSpriteSheet, string label, int x, int y);
	void render(SDL_Renderer * gRenderer);
	void setPosition(int x, int y);
private:
	Word * label;
	Point position;
	LTexture * btnTexture;
	enum ANIMATION_FRAMES { BUTTON_FRAMES = 3 };
	SDL_Rect spriteClips[BUTTON_FRAMES];
	int spriteIndex;
	int width;
	int height;
};

