#include "pch.h"
#include "Character.h"
#include "constants.h"

Character::Character()
{
	w = (int) (60 * scale);
	h = (int) (77 * scale);
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
	w = (int) (60 * scale);
	h = (int) (77 * scale);
	this->charRect.w = w;
	this->charRect.h = h;
	this->SetPosition(0, 0);
}
void Character::SetTexture(LTexture* alphabetsSpriteSheet)
{
	this->alphabetsSpriteSheet = alphabetsSpriteSheet;
}
void Character::SetPosition(int x, int y)
{
	this->position.x = x;
	this->position.y = y;
}

void Character::Render(SDL_Renderer * gRenderer)
{
	alphabetsSpriteSheet -> RenderTexture(this->position.x, this->position.y, gRenderer, &charRect, SDL_FLIP_NONE, 0.0, 0, scale);
}
void Character::SetChar(char c)
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

void Character::SetScale(float scale)
{
	this->scale = scale;
}

int Character::GetWidth()
{
	return w;
}

int Character::GetHeight()
{
	return h;
}

int Character::GetX() 
{
	return this->position.x;
}
int Character::GetY()
{
	return this->position.y;
}