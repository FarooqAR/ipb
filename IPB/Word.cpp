#include "pch.h"
#include <stdio.h>
#include "LTexture.h"
#include "Word.h"
#include "constants.h"

Word::Word(string str, LTexture * gSpriteSheetTexture, int x, int y, float scale)
{
	this->scale = scale;
	this->charSpacing = 30 * scale;
	this->txtTexture = gSpriteSheetTexture;
	this->setText(str);
	this->setPosition(x, y);
}
Word::~Word()
{
}
int Word::getTextLength()
{
	return this->renderWord.length();
}
void Word::setXCentered()
{
	int x = constants::WINDOW_WIDTH - renderWord.length() * constants::CHARACTER_WIDTH * scale + (renderWord.length() - 1) * 30 * scale;
	x = x / 2;
	setPosition(x, position.y);
}
void Word::setYCentered()
{
	int y = constants::WINDOW_HEIGHT - constants::CHARACTER_HEIGHT * scale;
	y = y / 2;
	setPosition(position.x, y);
}
void Word::setPosition(int x, int y)
{
	this->position.x = x;
	this->position.y = y;
	for (int i = 0; i < this->renderWord.length(); i++)
	{
		characters[i].setPosition(x + i * charSpacing, y);
	}
}
void Word::render(SDL_Renderer * gRenderer)
{
	for (int i = 0; i < this->renderWord.length(); i++)
	{
		characters[i].render(gRenderer);
	}
}
void Word::setText(string str)
{
	this->renderWord = str;
	if (this->characters != NULL)
	{
		delete[] this->characters;
	}
	this->characters = new Character[str.length()];
	for (int i = 0; i < this->renderWord.length(); i++)
	{
		this->characters[i].setTexture(this->txtTexture);
		this->characters[i].setChar(str[i]);
		this->characters[i].setScale(this->scale);
	}
}
int Word::getX()
{
	return this->position.x;
}
int Word::getY()
{
	return this->position.y;
}