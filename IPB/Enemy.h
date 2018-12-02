#pragma once
#include <SDL.h>
#include "Unit.h"
#include "Weapon.h"

class Enemy : public Unit
{
public:
	Enemy(SDL_Renderer* renderer, LTexture* imageSpriteSheet, int initialX, int initialY);
	~Enemy();
	void SetHealth(float);
	void Move();
	float GetHealth();
	Weapon* GetWeapon();

private:
	float health;
	Weapon* weapon;
};

