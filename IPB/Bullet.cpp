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
	position.x += (cos((angle - 90) * M_PI / 180)) * 10;
	position.y += (sin((angle - 90) * M_PI / 180)) * 10;
	if (position.y < -100 || position.y > constants::WINDOW_HEIGHT || position.x <  -100 || position.x > constants::WINDOW_WIDTH)
	{
		setAlive(false);
	}
}

Bullet::~Bullet()
{
	delete objTexture;
}

Bullet::Bullet(SDL_Renderer* gRenderer, const char * filename, int x, int y, float scale, double angle, int damage) : Unit()
{
	setPosition(x, y);
	objTexture = new LTexture;
	renderer = gRenderer;
	this->scale = scale;
	objTexture->loadFromFile(filename, gRenderer);
	this->width = this->objTexture->getWidth() * scale;
	this->height = this->objTexture->getHeight() * scale;
	this->angle = angle;
	this->damage = damage;
}
