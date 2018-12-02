#include "pch.h"
#include "Bullet.h"
#include "LTexture.h"
#include "constants.h"

#include <cmath>


//constructors
Bullet::Bullet()
{
	alive = true;
}

Bullet::Bullet(SDL_Renderer* gRenderer, LTexture* imageSpriteSheet, int bulletType, int x, int y, float scale, double angle, int damage, int bulletWidth, int bulletHeight) : Unit()
{
	SetPosition(x, y);
	objTexture = imageSpriteSheet;
	renderer = gRenderer;
	this->scale = scale;
	this->destRect = {
		constants::BULLETS_SPRITE_START_POSITION.x + bulletWidth * bulletType,
		constants::BULLETS_SPRITE_START_POSITION.y,
		bulletWidth,
		bulletHeight
	};
	this->width = (int)(bulletWidth * scale);
	this->height = (int)(bulletHeight * scale);
	this->angle = angle;
	this->damage = damage;
}

//destructor
Bullet::~Bullet()
{
	delete objTexture;
}


void Bullet::Move()
{
	position.x += (int)(cos((angle - 90) * constants::PI / 180) * 10);
	position.y += (int)(sin((angle - 90) * constants::PI / 180) * 10);
	//deletes bullet once out of the game screen frame
	if (position.y < -100 || position.y > constants::WINDOW_HEIGHT || position.x <  -100 || position.x > constants::WINDOW_WIDTH)
	{
		SetAlive(false);
	}
}

