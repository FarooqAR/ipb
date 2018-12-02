#include "pch.h"
#include "Asteroid.h"
#include <cmath>


//randomly sets the initial position of the asteroid
void Asteroid::SetPosition()
{
	int x = 0;
	int y = 0;

	//coming from either the sides of the screen or top/bottom
	if (rand() % 2 == 1)
	{
		y = rand() % 700;
		if (rand() % 2 == 1)
		{
			x = -90;
			direction = 'l';
		}
		else
		{
			x = constants::WINDOW_WIDTH ;
			direction = 'r';
		}
	}
	else
	{
		x = rand() % 1024;
		if (rand() % 2 == 1)
		{
			y = -10;
			direction = 'u';
		}
		else
		{
			y = constants::WINDOW_HEIGHT;
			direction = 'd';
		}
	}
	this->setPosition(x, y);

}

//Constructors
Asteroid::Asteroid()
{
	alive = true;
}


Asteroid::Asteroid(SDL_Renderer* gRenderer, LTexture* imageSpriteSheet,float scale, int damage, int speedX, int speedY) : Unit()
{
	SetPosition();
	this->angle = (position.x <= 512 || position.y <= 350) ? rand() % 91 + 90 : rand() % 91 + 180;
	this->objTexture = imageSpriteSheet;
	this->renderer = gRenderer;
	this->scale = scale;
	this->alive = true;
	this->width = constants::ASTEROID_WIDTH;
	this->height = constants::ASTEROID_HEIGHT;
	this->damage = damage;
	this->speedX = speedX;
	this->speedY = speedY;

}

//Destructor
Asteroid::~Asteroid()
{

}

//Moves the asteroid 
void Asteroid::move()
{
	if (direction == 'l' || direction == 'u')
	{
		position.x += (sin((angle - 90) * M_PI / 180)) * speedX;
		position.y += (cos((angle - 90) * M_PI / 180)) * speedY;
	}
	else if (direction == 'd' || direction == 'r')
	{
		position.x -= (sin((angle - 90) * M_PI / 180)) * speedX;
		position.y += (cos((angle - 90) * M_PI / 180)) * speedY;
	}

	if (position.y < -100 || position.y > constants::WINDOW_HEIGHT + 20 || position.x <  -100 || position.x > constants::WINDOW_WIDTH + 20)
	{
		setAlive(false);
	}
}
