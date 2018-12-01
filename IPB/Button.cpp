#include "pch.h"
#include "constants.h"
#include "Button.h"
#include "Point.h"

Button::Button()
{
	this->label = nullptr;
}
Button::Button(LTexture * bgTexture, LTexture * alphabetsSpriteSheet, string label, int x, int y, int w, int h )
{
	width = w;
	height = h;
	spriteIndex = 0;
	this->btnTexture = bgTexture; 
	float labelScale = 0.7;
	int labelX = width - label.length() * 60 * labelScale + (label.length() - 1) * 30 * labelScale;
	this->label = new Word(
		label, 
		alphabetsSpriteSheet, 
		x + labelX/2,
		y, 
		labelScale
	);
	setPosition(x, y);
}

Button::Button(LTexture * imagesSpriteSheet, string label, int x, int y, int w, int h)
{
	width = w;
	height = h;
	Point spritePos = constants::BUTTONS_SPRITE_START_POSITION;
	spriteClips[0] = { spritePos.x, spritePos.y, width, height };
	spriteClips[1] = { spritePos.x, spritePos.y + 56, width, height };
	spriteClips[2] = { spritePos.x, spritePos.y + 109, width, height };
	spriteIndex = 0;
	this->btnTexture = imagesSpriteSheet;
	float labelScale = 0.7;
	int labelX = width - label.length() * 60 * labelScale + (label.length() - 1) * 30 * labelScale;
	this->label = new Word(
		label,
		imagesSpriteSheet,
		x + labelX / 2,
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
		&spriteClips[spriteIndex]
	);
	this->label->render(gRenderer);
}

void Button::setPosition(int x, int y)
{
	this->position.x = x;
	this->position.y = y;
}

void Button::onHover(int clickX, int clickY)
{
	if (clickX >= position.x &&
		clickX <= position.x + width &&
		clickY >= position.y &&
		clickY <= position.y + height)
		spriteIndex = 1;
	else
		spriteIndex = 0;
}
void Button::onClickDown(int clickX, int clickY)
{
	if (clickX >= position.x &&
		clickX <= position.x + width &&
		clickY >= position.y &&
		clickY <= position.y + height)
		spriteIndex = 2;
}
bool Button::onClickUp(int clickX, int clickY)
{
	if (clickX >= position.x &&
		clickX <= position.x + width &&
		clickY >= position.y &&
		clickY <= position.y + height)
	{
		spriteIndex = 1;
		return true;
	}
	return false;
}
Button::~Button()
{
}
