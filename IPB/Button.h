#pragma once
#include "LTexture.h"
#include "Word.h"

class Button
{
public:
	~Button();
	Button(LTexture * Texture, string str, int x, int y);
	void render(SDL_Renderer * gRenderer);
	void setPosition(int x, int y);
	void setText(const char*);
	Word * word;
private:
	int x, y;
	SDL_Rect BtnRect[3];
	LTexture * btnTexture;
};