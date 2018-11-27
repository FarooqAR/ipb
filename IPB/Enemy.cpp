#include "pch.h"
#include "Enemy.h"


Enemy::Enemy(SDL_Renderer * gRenderer, int initialX, int initialY)
{
	this->objTexture = new LTexture;
	this->weapon = new Weapon("gun", 10, 2);
	this->objTexture->loadFromFile("assets/ufo.png", gRenderer);
	this->setPosition(initialX, initialY);
	this->renderer = gRenderer;
	this->width = 100;
	this->height = 63;
	this->health = 100;
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
