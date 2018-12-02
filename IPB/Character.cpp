#include "pch.h"
#include "Character.h"
#include "constants.h"

Character::Character()
{
	w = static_cast<int>(60 * scale);
	h = static_cast<int>(77 * scale);
	this->charRect.w = w;
	this->charRect.h = h;
}

Character::~Character()
{

}

Character::Character(char c, LTexture* alphabetsSpriteSheet)
{
	this->showChar = c;
	this->alphabetsSpriteSheet = alphabetsSpriteSheet;
	w = static_cast<int>(60 * scale);
	h = static_cast<int>(77 * scale);
	this->charRect.w = w;
	this->charRect.h = h;
	this->setPosition(0, 0);
}
void Character::setTexture(LTexture* alphabetsSpriteSheet)
{
	this->alphabetsSpriteSheet = alphabetsSpriteSheet;
}
void Character::setPosition(int x, int y)
{
	this->position.x = x;
	this->position.y = y;
}

void Character::render(SDL_Renderer * gRenderer)
{
	alphabetsSpriteSheet -> renderTexture(this->position.x, this->position.y, gRenderer, &charRect, SDL_FLIP_NONE, 0.0, 0, scale);
}
void Character::setChar(char c)
{
	int ascii = c;
	if (ascii >= 32 && ascii <= 122)
	{
		ascii -= 32;
	    this->charRect.x = constants::ALPHABETS_SPRITE_START_POSITION.x + ascii * 60;
	    this->charRect.y = constants::ALPHABETS_SPRITE_START_POSITION.y;
	}
	else
	{
		this->charRect.x = 0;
		this->charRect.y = 0;
	}
}

void Character::setScale(float scale)
{
	this->scale = scale;
}

int Character::getWidth()
{
	return w;
}

int Character::getHeight()
{
	return h;
}

int Character::getX() 
{
	return this->position.x;
}
int Character::getY()
{
	return this->position.y;
}