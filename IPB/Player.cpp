#include "pch.h"
#include "Player.h"
#include <cmath>


Player::Player(SDL_Renderer* gRenderer, int initialX, int initialY)
{
	this->objTexture = new LTexture;
	this->objTexture->loadFromFile("assets/herosprite.png", gRenderer);
	this->setPosition(initialX, initialY);
	this->renderer = gRenderer;
	this->width = 36;
	this->height = 60;
	this->health = 100;
	this->fuel = 100;
	this->oxygen = 100;
	this->shipCurrentClipIndex = 0;
	for (int i = 0; i < 3; i++)
	{
		shipSpriteClips[i] = { this->width * i, 0, this->width, this->height };
	}
}
void Player::render()
{
	this->objTexture->renderTexture(
		position.x,
		position.y,
		renderer,
		&shipSpriteClips[this->shipCurrentClipIndex],
		SDL_FLIP_NONE,
		this->angle,
		nullptr,
		scale,
		false // if true, shows red rectangle around the unit for debugging purposes
	);
}
void Player::setShipCurrentClipIndex(int i)
{
	this->shipCurrentClipIndex = i;
}
void Player::setHealth(int health)
{
	if (this->health > 0 && this->health <= 100)
		this->health = health;
	else
	{
		this->health = 0;
		this->alive = false;
	}
}

void Player::setOxygen(int oxygen)
{
	if (this->oxygen > 0 && this->oxygen <= 100)
		this->oxygen = oxygen;
	else
	{
		this->oxygen = 0;
		this->alive = false;
	}
}
void Player::setFuel(int fuel)
{
	if (this->fuel > 0 && this->fuel <= 100)
		this->fuel = fuel;
	else
	{
		this->fuel = 0;
		this->alive = false;
	}
}
int Player::getHealth()
{
	return health;
}
int Player::getOxygen()
{
	return oxygen;
}

int Player::getFuel()
{
	return fuel;
}

int Player::getCurrentClipIndex()
{
	return shipCurrentClipIndex;
}

void Player::GetPulled()
{
	
}
