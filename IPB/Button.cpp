#include "pch.h"
#include "Button.h"

Button::Button()
{
	this->label = nullptr;
}
Button::Button(LTexture * bgTexture, LTexture * alphabetsSpriteSheet, string label, int x, int y)
{
	spritRect = { 0, 0, 300, 52 };
	this->btnTexture = bgTexture; 
	float labelScale = 0.7;
	int labelX = 300 - label.length() * 60 * labelScale + (label.length() - 1) * 30 * labelScale;
	this->label = new Word(
		label, 
		alphabetsSpriteSheet, 
		x + labelX/2,
		y, 
		labelScale
	);
	setPosition(x, y);
}

void Button::render(SDL_Renderer * gRenderer)
{
	this->btnTexture->renderTexture(
		this->position.x,
		this->position.y,
		gRenderer,
		&spritRect
	);
	this->label->render(gRenderer);
}

void Button::setPosition(int x, int y)
{
	this->position.x = x;
	this->position.y = y;
}



Button::~Button()
{
}