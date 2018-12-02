#include "pch.h"
#include "Enemy.h"
#include "constants.h"


Enemy::Enemy(SDL_Renderer * gRenderer, LTexture* imageSpriteSheet, int initialX, int initialY)
{
	this->objTexture = imageSpriteSheet;
	this->weapon = new Weapon(10, constants::SIMPLE_BULLET);
	this->setPosition(initialX, initialY);
	this->renderer = gRenderer;
	this->width = constants::ENEMY_WIDTH;
	this->height = constants::ENEMY_HEIGHT;
	this->health = 100;
	this->destRect = { 
		constants::ENEMY_SPRITE_START_POSITION.x, 
		constants::ENEMY_SPRITE_START_POSITION.y, 
		constants::ENEMY_WIDTH,
		constants::ENEMY_HEIGHT
	};
}

Enemy::~Enemy()
{
}

void Enemy::setHealth(float health)
{
	if (health > 0 && health <= 100)
		this->health = health;
	else
	{
		this->health = 0;
		this->alive = false; 
	}
}

float Enemy::getHealth()
{
	return this->health;
}

Weapon * Enemy::getWeapon()
{
	return weapon;
}

void Enemy::move()
{
	if (position.x > constants::WINDOW_WIDTH / 2)
	{
		speedX = speedX - .01f;
	}
	if (position.x < constants::WINDOW_WIDTH / 2)
	{
		speedX = speedX + .01f;
	}
	

	position.x = (int) (position.x + speedX);



}
