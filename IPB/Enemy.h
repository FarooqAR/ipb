#pragma once
#include <SDL.h>
#include "Unit.h"
#include "Weapon.h"

class Enemy : public Unit
{
public:
	Enemy(SDL_Renderer* renderer, LTexture* imageSpriteSheet, int initialX, int initialY);
	~Enemy();
	void setHealth(float);
	float getHealth();
	Weapon* getWeapon();

private:
	float health;
	Weapon* weapon;
};

