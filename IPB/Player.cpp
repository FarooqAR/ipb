#include "pch.h"
#include "Player.h"
#include <cmath>


Player::Player(SDL_Renderer* gRenderer, int initialX, int initialY)
{
	this->objTexture = new LTexture;
	this->objTexture->loadFromFile("assets/herosprite1.png", gRenderer);
	this->setPosition(initialX, initialY);
	this->renderer = gRenderer;
	this->width = 36;
	this->height = 75;
	this->health = 100;
	this->fuel = 100;
	this->oxygen = 100;
	this->shipCurrentClipIndex = 0;
	for (int i = 0; i < 11; i++)
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
void Player::changeShipCurrentClipIndex()
{
	if (shipCurrentClipIndex > 3 && shipCurrentClipIndex < 8)
		shipCurrentClipIndex++;
	else
		shipCurrentClipIndex = 4;
}
void Player::setHealth(float health)
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
float Player::getHealth()
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

bool Player::getIsThrusting()
{
	return isThrusting;
}

void Player::setIsThrusting(bool b)
{
	isThrusting = b;
}