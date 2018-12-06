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
	explode = false;

}

Unit::Unit(SDL_Renderer* renderer, LTexture* unitTexture, float scale, bool alive, double angle)
	:scale(scale), alive(alive), angle(angle), objTexture(unitTexture), renderer(renderer)
{
	
}
Unit::~Unit()
{
}
bool Unit::CheckCollision(Unit* unit)
{
	//checks for collisions
	if (position.x + width < unit->GetPosition().x ||
		position.x > unit->GetPosition().x + unit->GetWidth() ||
		position.y + height < unit->GetPosition().y ||
		position.y > unit->GetPosition().y + unit->GetHeight())
	{
		return false;
	}
	return true;
}
bool Unit::CheckCollision(Unit* unit, bool isCentered)
{
	//checks for collisions
	if ((unit->GetPosition().x >= position.x  &&
		unit->GetPosition().x <= position.x + width) &&
		(unit->GetPosition().y >= position.y &&
		unit->GetPosition().y <= position.y + height))
	{
		return true;
	}
	return false;
}

void Unit::SetAlive(bool alive)
{
	this->alive = alive;
}
void Unit::Explode()
{
	this->explode = true;
}
bool Unit::GetExplode()
{
	return explode;
}
bool Unit::GetAlive()
{
	return alive;
}

void Unit::SetPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}
void Unit::Move(int direction)
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
		//vectorize thrust
		speedX += (float) (cos((angle - 90) * constants::PI / 180)*thrust);
		speedY += (float) (sin((angle - 90) * constants::PI / 180)*thrust);

		//gets the decimal value
		speedXdecimal = speedX - floor(speedX);
		speedYdecimal = speedY - floor(speedY);

		//moves that decimal value in pixels
		if (speedXdecimal != 0)
		{
			if (count1 %static_cast<int>(1 / speedXdecimal) == 0)
				position.x += (int) (1 * (speedXdecimal / abs(speedXdecimal)));
		}
		if (speedYdecimal != 0)
		{
			if (count1%static_cast<int>(1 / speedYdecimal) == 0)
				position.y += (int) (1 * (speedYdecimal / abs(speedYdecimal)));
		}

		count1++;

		//changes position
		position.x += (int) speedX;
		position.y += (int) speedY;
	}

}

void Unit::Move()
{
	
	//gets the decimal value
	speedXdecimal = speedX - floor(speedX);
	speedYdecimal = speedY - floor(speedY);

	//moves that decimal value in pixels
	if (speedXdecimal != 0)
	{
		if (count1 %static_cast<int>(1 / speedXdecimal) == 0)
			position.x += (int) (1 * (speedXdecimal / abs(speedXdecimal)));
	}
	if (speedYdecimal != 0)
	{
		if (count1%static_cast<int>(1 / speedYdecimal) == 0)
			position.y += (int) (1 * (speedYdecimal / abs(speedYdecimal)));
	}

	//changes position
	position.x += (int) speedX;
	position.y += (int) speedY;


	//teleports from sides
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


Point Unit::GetPosition()
{
	return position;
}
int Unit::GetWidth()
{
	return width;
}

int Unit::GetHeight()
{
	return height;
}

void Unit::SetAngle(double angle)
{
	this->angle = angle;
}

double Unit::GetAngle()
{
	return this->angle;
}

void Unit::Render()
{
	if (explode)
	{
		if (explosionSpriteIndex < 20)
		{
			objTexture->RenderTexture(
				position.x,
				position.y,
				renderer, 
				&explosionSpriteClips[explosionSpriteIndex]
			);
			explosionSpriteIndex++;
		}
		else
		{
			SetAlive(false);
		}
	}
	else
	{
		this->objTexture->RenderTexture(
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
	
}

void Unit::SetScale(float scale)
{
	if (scale >= 0 && scale <= 1)
		this->scale = scale;
}

void Unit::SetClip(SDL_Rect clip)
{
	width = clip.w;
	height = clip.h;
	destRect = clip;
}

float Unit::GetScale()
{
	return this->scale;
}
void Unit::SetSpeed(float x, float y)
{
	this->speedX = x;
	this->speedY = y;
}

float Unit::GetXSpeed()
{
	return speedX;
}

float Unit::GetYSpeed()
{
	return speedY;
}
