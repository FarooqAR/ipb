#include "pch.h"
#include "Bullet.h"
#include "LTexture.h"
#include "constants.h"

#include <cmath>



Bullet::Bullet()
{
	alive = true;
}

void Bullet::move()
{
	position.x += static_cast<int>((cos((angle - 90) * constants::PI / 180)) * 10);
	position.y += static_cast<int>((sin((angle - 90) * constants::PI / 180)) * 10);
	if (position.y < -100 || position.y > constants::WINDOW_HEIGHT || position.x <  -100 || position.x > constants::WINDOW_WIDTH)
	{
		setAlive(false);
	}
}

Bullet::~Bullet()
{
	delete objTexture;
}

Bullet::Bullet(SDL_Renderer* gRenderer, LTexture* imageSpriteSheet, int bulletType, int x, int y, float scale, double angle, int damage, int bulletWidth, int bulletHeight) : Unit()
{
	setPosition(x, y);
	objTexture = imageSpriteSheet;
	renderer = gRenderer;
	this->scale = scale;
	this->destRect = { 
		constants::BULLETS_SPRITE_START_POSITION.x + bulletWidth * bulletType,
		constants::BULLETS_SPRITE_START_POSITION.y, 
		bulletWidth, 
		bulletHeight 
	};
	this->width = static_cast<int>(bulletWidth * scale);
	this->height = static_cast<int>(bulletHeight * scale);
	this->angle = angle;
	this->damage = damage;
}
