#pragma once

#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<stdio.h>

using namespace std;

class LTexture
{
private:
	SDL_Texture* texture;
	int width;
	int height;

public:
	LTexture();
	~LTexture();
	bool loadFromFile(const char*, SDL_Renderer*, bool flagColorKey = true, Uint8 redColorKey = 0, Uint8 greenColorKey = 0xFF, Uint8 blueColorKey = 0xFF);        ///takes arguments to ColorKey
	void renderTexture(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE, double angle = 0.0, SDL_Point* center = NULL, float scale = 1, bool debug = false);
	void free();
	//Set blending
	void setBlendMode(SDL_BlendMode blending);
	//Set alpha modulation
	void setAlpha(Uint8 alpha);
	int getWidth();
	int getHeight();
};
