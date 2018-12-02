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
	void OnHover(int clickX, int clickY);
	void OnClickDown(int clickX, int clickY);
	bool OnClickUp(int clickX, int clickY);
	Button(LTexture * bgTexture, LTexture * alphabetsSpriteSheet, string label, int x, int y, int w = 300, int h = 52);
	Button(LTexture * imagesSpriteSheet, string label, int x, int y, int w = 300, int h = 52);
	void Render(SDL_Renderer * gRenderer);
	void SetPosition(int x, int y);
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

