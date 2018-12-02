#include "pch.h"
#include <stdio.h>
#include "LTexture.h"
#include "Word.h"
#include "constants.h"

Word::Word(string str, LTexture * imagesSpriteSheet, int x, int y, float scale)
{
	this->scale = scale;
	this->charSpacing = (int) (30 * scale);
	this->txtTexture = imagesSpriteSheet;
	this->SetText(str);
	this->SetPosition(x, y);
}
Word::~Word()
{
}
int Word::GetTextLength()
{
	return this->renderWord.length();
}
void Word::SetXCentered()
{
	int x = (int) (constants::WINDOW_WIDTH - renderWord.length() * constants::CHARACTER_WIDTH * scale + (renderWord.length() - 1) * 30 * scale);
	x = x / 2;
	SetPosition(x, position.y);
}
void Word::SetYCentered()
{
	int y = (int)(constants::WINDOW_HEIGHT - constants::CHARACTER_HEIGHT * scale);
	y = y / 2;
	SetPosition(position.x, y);
}
void Word::SetPosition(int x, int y)
{
	this->position.x = x;
	this->position.y = y;
	for (size_t i = 0; i < this->renderWord.length(); i++)
	{
		characters[i].SetPosition(x + i * charSpacing, y);
	}
}
void Word::Render(SDL_Renderer * gRenderer)
{
	for (size_t i = 0; i < (unsigned) this->renderWord.length(); i++)
	{
		characters[i].Render(gRenderer);
	}
}
void Word::SetText(string str)
{
	this->renderWord = str;
	if (this->characters != NULL)
	{
		delete[] this->characters;
	}
	this->characters = new Character[str.length()];
	for (size_t i = 0; i < (unsigned) this->renderWord.length(); i++)
	{
		this->characters[i].SetTexture(this->txtTexture);
		this->characters[i].SetChar(str[i]);
		this->characters[i].SetScale(this->scale);
	}
	SetPosition(position.x, position.y);
}
int Word::GetX()
{
	return this->position.x;
}
int Word::GetY()
{
	return this->position.y;
}