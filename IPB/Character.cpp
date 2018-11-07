#include"Character.h"
#include<iostream>
Character::Character()
{

}

Character::Character(char c, LTexture * gSpriteSheetTexture)
{
	this -> shownChar = c;
	this -> CharTexture = gSpriteSheetTexture;
	this -> charRect.w = 88;
	this -> charRect.h = 99;
	this -> setPosition(10, 10);
	this -> setChar(c);
}
Character::~Character()
{
	/*char n = character_value + 97;
	std::cout<<"\nCharacter "<<n<<" Destroyed";*/
}
void Character::setPosition(int x, int y)
{
	this -> x = x;
	this -> y = y;
}
void Character::setChar(char c)
{
	int ascii = c;
	if (c == ' ')
	{
		this -> charRect.x = 4 * 88;
		this -> charRect.y = 5 * 99;
	}
	if (ascii <= 90 && ascii >= 65)
	{
		ascii -= 65;
		this -> charRect.x = (ascii % 5) * 88;
		this -> charRect.y = (ascii / 5) * 99;
	}
}
void Character::render(SDL_Renderer * gRenderer)
{
	CharTexture -> renderTexture(this -> x, this -> y, gRenderer, &charRect);
}
void Character::setTexture(LTexture * gSpriteSheetTexture, char c)
{
	this -> shownChar = c;
	this -> CharTexture = gSpriteSheetTexture;
	this -> charRect.w = 88;
	this -> charRect.h = 99;
	this -> setPosition(10, 10);
	this -> setChar(c);
}

