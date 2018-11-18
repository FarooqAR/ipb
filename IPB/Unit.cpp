#include "pch.h"
#include "Unit.h"
#include <iostream>
#include <cmath>
using namespace std;


Unit::Unit()
{
	scale = 1;
	alive = 1;
	angle = 0.0;
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
		this->angle -= 1.0;
	}

	if (direction == RIGHT)
	{
		this->angle += 1.0;
		cout << "angle: " << angle << endl;
	}

	if (direction == UP)
	{
		position.x += cos((angle - 90) * M_PI / 180)  * 4.5;
		position.y += sin((angle - 90) * M_PI / 180) * 4.5;
	}

}

void Unit::move()
{
	//speedX *= 0.5;
	//speedY *= 0.5;

	//position.x += cos((angle - 90) * M_PI / 180) * speedX;
	//position.y += sin((angle - 90) * M_PI / 180) * speedY;
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
		nullptr,
		SDL_FLIP_NONE,
		this->angle,
		nullptr,
		scale,
		false // if true, shows red rectangle around the unit for debugging purposes
	);
}
