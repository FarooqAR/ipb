#include "pch.h"
#include"LTexture.h"
#include <iostream>
using namespace std;

LTexture::LTexture()
{
	texture = NULL;
	width = 0;
	height = 0;
}

LTexture::~LTexture()
{
	free();
}

bool LTexture::loadFromFile(const char* path, SDL_Renderer* gRenderer, bool flagColorKey, Uint8 redColorKey, Uint8 greenColorKey, Uint8 blueColorKey)
{
	SDL_Surface* loadedSurface = NULL;
	SDL_Texture* newTexture = NULL;

	loadedSurface = IMG_Load(path);
	if (loadedSurface == NULL)
	{
		cout << "Unable to load image from " << path << ". SDL_image error" << IMG_GetError() << endl;
	}
	else
	{
		SDL_SetColorKey(loadedSurface, flagColorKey, SDL_MapRGB(loadedSurface->format, redColorKey, greenColorKey, blueColorKey));
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

		if (newTexture != NULL)
		{
			width = loadedSurface->w;
			height = loadedSurface->h;
		}
		else
		{
			cout << "Unable to create texture from surface from " << path << ". SDL_image error" << IMG_GetError() << endl;
		}

		SDL_FreeSurface(loadedSurface);
	}
	texture = newTexture;
	return texture != NULL;
}


void LTexture::renderTexture(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip, SDL_RendererFlip flip, double angle, SDL_Point* center, float scale, bool debug)
{
	SDL_Rect rectCoordinates = { x, y, width, height };
	
	if (clip != NULL)
	{
		rectCoordinates.w = clip->w;
		rectCoordinates.h = clip->h;
	}
	rectCoordinates.w *= scale;
	rectCoordinates.h *= scale;
	if (debug == true)
	{
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderDrawRect(gRenderer, &rectCoordinates);
	}
	SDL_RenderCopyEx(gRenderer, texture, clip, &rectCoordinates, angle, center, flip);
}

void LTexture::free()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}
}


int LTexture::getWidth()
{
	return width;
}

int LTexture::getHeight()
{
	return height;
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(texture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(texture, alpha);
}
