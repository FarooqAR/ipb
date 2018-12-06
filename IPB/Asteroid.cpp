#include "pch.h"
#include "Asteroid.h"
#include <cmath>


//randomly sets the initial position of the asteroid
void Asteroid::SetPosition()
{
	int x = 0;
	int y = 0;

	//random selection of direction of asteroids coming 
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
	((Unit*) (this))->SetPosition(x, y);

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
	this->explosionSpriteIndex = 0;
	this->alive = true;
	this->width = (int) (constants::ASTEROID_WIDTH * scale);
	this->height = (int) (constants::ASTEROID_HEIGHT * scale);
	this->damage = damage;
	this->speedX = (float) speedX;
	this->speedY = (float) speedY;
	this->explode = false;
	for (int i = 0; i < 20; i++)
	{
		explosionSpriteClips[i] = {
			constants::EXPLOSION_SPRITE_START_POSITION.x + 96 * i,
			constants::EXPLOSION_SPRITE_START_POSITION.y,
			96, 96
		};
	}

}

//Destructor
Asteroid::~Asteroid()
{

}

//Moves the asteroid 
void Asteroid::Move()
{
	if (direction == 'l' || direction == 'u')
	{
		position.x += (int) ((sin((angle - 90) * M_PI / 180)) * speedX);
		position.y += (int) ((cos((angle - 90) * M_PI / 180)) * speedY);
	}
	else if (direction == 'd' || direction == 'r')
	{
		position.x -= (int)((sin((angle - 90) * M_PI / 180)) * speedX);
		position.y += (int)((cos((angle - 90) * M_PI / 180)) * speedY);
	}

	//deletes the asteroid object once it is out of the game screen frame
	if (position.y < -100 || position.y > constants::WINDOW_HEIGHT + 20 || position.x <  -100 || position.x > constants::WINDOW_WIDTH + 20)
	{
		Unit::SetAlive(false);
	}
}