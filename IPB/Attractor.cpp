#include "pch.h"
#include "Attractor.h"
#include "LTexture.h"

Attractor::Attractor()
{
	// hello world;
}

Attractor::Attractor(SDL_Renderer* gRenderer, double mass, double radius, const char * filename, int x, int y, float scale)
{
	this->setPosition(x, y);
	this->objTexture = new LTexture;
	this->renderer = gRenderer;
	this->scale = scale;
	this->objTexture->loadFromFile(filename, gRenderer);
	this->width = this->objTexture->getWidth() * scale;
	this->height = this->objTexture->getHeight() * scale;
}
