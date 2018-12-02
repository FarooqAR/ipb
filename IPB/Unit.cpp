#include "pch.h"
#include "constants.h"
#include "Unit.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;


Unit::Unit()
{
	scale = 1;
	alive = 1;
	angle = 0.0;	
}

Unit::Unit(SDL_Renderer* renderer, LTexture* unitTexture, float scale, bool alive, double angle)
	:scale(scale), alive(alive), angle(angle), objTexture(unitTexture), renderer(renderer)
{
	
}
Unit::~Unit()
{
}
bool Unit::checkCollision(Unit* unit)
{
	if (position.x + width < unit->getPosition().x ||
		position.x > unit->getPosition().x + unit->getWidth() ||
		position.y + height < unit->getPosition().y ||
		position.y > unit->getPosition().y + unit->getHeight())
	{
		return false;
	}
	return true;
}
bool Unit::checkCollision(Unit* unit, bool isCentered)
{
	if ((unit->getPosition().x >= position.x  &&
		unit->getPosition().x <= position.x + width) &&
		(unit->getPosition().y >= position.y &&
		unit->getPosition().y <= position.y + height))
	{
		return true;
	}
	return false;
}

void Unit::setAlive(bool alive)
{
	this->alive = alive;
}

bool Unit::getAlive()
{
	return alive;
}

void Unit::setPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}
void Unit::move(int direction)
{


	if (direction == LEFT)
	{
		this->angle -= 3;
	}

	if (direction == RIGHT)
	{
		this->angle += 3;
	}

	if (direction == UP)
	{
		speedX += cos((angle - 90) * constants::PI / 180)*thrust;
		speedY += sin((angle - 90) * constants::PI / 180)*thrust;
		speedXdecimal = speedX - floor(speedX);
		speedYdecimal = speedY - floor(speedY);
		if (speedXdecimal != 0)
		{
			if (count1 %static_cast<int>(1 / speedXdecimal) == 0)
				position.x += 1 * (speedXdecimal / abs(speedXdecimal));
		}
		if (speedYdecimal != 0)
		{
			if (count1%static_cast<int>(1 / speedYdecimal) == 0)
				position.y += 1 * (speedYdecimal / abs(speedYdecimal));
		}

		count1++;
		position.x += speedX;
		position.y += speedY;
	}

}

void Unit::move()
{
	
	speedXdecimal = speedX - floor(speedX);
	speedYdecimal = speedY - floor(speedY);

	//cout << "deltaX" << speedX << "        deltaY" << speedY << "  " << count1 << endl;


	if (speedXdecimal != 0)
	{
		if (count1 %static_cast<int>(1 / speedXdecimal) == 0)
			position.x += 1 * (speedXdecimal / abs(speedXdecimal));
	}
	if (speedYdecimal != 0)
	{
		if (count1%static_cast<int>(1 / speedYdecimal) == 0)
			position.y += 1 * (speedYdecimal / abs(speedYdecimal));
	}

	position.x += speedX;
	position.y += speedY;

	if (position.x < 0)
	{
		position.x = constants::WINDOW_WIDTH;
	}
	if (position.x > constants::WINDOW_WIDTH)
	{
		position.x = 0;
	}
	if (position.y < 0)
	{
		position.y = constants::WINDOW_HEIGHT;
	}
	if (position.y > constants::WINDOW_HEIGHT)
	{
		position.y = 0;
	}
	count1++;

}


Point Unit::getPosition()
{
	return position;
}
int Unit::getWidth()
{
	return width;
}

int Unit::getHeight()
{
	return height;
}

void Unit::setAngle(double angle)
{
	this->angle = angle;
}

double Unit::getAngle()
{
	return this->angle;
}

void Unit::render()
{
	this->objTexture->renderTexture(
		position.x,
		position.y,
		renderer,
		&destRect,
		SDL_FLIP_NONE,
		this->angle,
		nullptr,
		scale,
		scale,
		false
	);
}

void Unit::setScale(float scale)
{
	if (scale >= 0 && scale <= 1)
		this->scale = scale;
}

void Unit::setClip(SDL_Rect clip)
{
	width = clip.w;
	height = clip.h;
	destRect = clip;
}

float Unit::getScale()
{
	return this->scale;
}
void Unit::setSpeed(float x, float y)
{
	this->speedX = x;
	this->speedY = y;
}

float Unit::getxSpeed()
{
	return speedX;
}

float Unit::getySpeed()
{
	return speedY;
}

void Unit::Explosion(LTexture* ExplosionTexture, SDL_Rect(&clip)[20], Unit* unit)
{
	int Index = 0;
	int Delay = 0;
	while (Index < 10)
	{
		ExplosionTexture->renderTexture((unit->position.x), (unit->position.y), renderer, &clip[Index]);
		if (Delay % 8 == 0)
		{
			Index++;
		}
		Delay++;
	}
}
