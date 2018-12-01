#include "pch.h"
#include "constants.h"
#include "Weapon.h"
#include <cmath>

Weapon::Weapon()
{
	bullets = nullptr;
	name = "Gun";
	WeaponType = constants::SIMPLE_BULLET;
	TimeDelay = 30;
	Ammo = 30;
}


Weapon::Weapon(const char* name, int delay, int type, int ammo)
{
	bullets = nullptr;
	this->name = name;
	WeaponType = type;
	TimeDelay = delay;
	Ammo = ammo;
}

Weapon::~Weapon()
{
	delete bullets;
}

int Weapon::GetDelay()
{
	return TimeDelay;
}

const char* Weapon::GetWeaponName()
{
	return name;
}
int Weapon::GetWeaponType()
{
	return WeaponType;
}
int Weapon::GetAmmo()
{
	return Ammo;
}

void Weapon::setWeaponName(const char * w_name)
{
	name = w_name;
}

Bullet* Weapon::Fire(SDL_Renderer* gRenderer, LTexture* imagesSpriteSheet, int xcord, int ycord, double angle)
{
	if (WeaponType == constants::SIMPLE_BULLET)
	{
		bullets = new Bullet(gRenderer, imagesSpriteSheet, WeaponType, xcord + cos((angle - 90) * constants::PI / 180) + 11, ycord + sin((angle - 90) * constants::PI / 180) + 11, 0.15, angle, 10, constants::BULLET_WIDTH, constants::BULLET_HEIGHT);
	}

	if (WeaponType == constants::MISSILE)
	{
		bullets = new Bullet(gRenderer, imagesSpriteSheet, WeaponType, xcord + cos((angle - 90) * constants::PI / 180) + 11, ycord + sin((angle - 90) * constants::PI / 180) + 11, 0.3, angle, 20, constants::BULLET_WIDTH, constants::MISSILE_HEIGHT);
	}

	if (WeaponType == constants::LASER)
	{
		bullets = new Bullet(gRenderer, imagesSpriteSheet, WeaponType, xcord + cos((angle - 90) * constants::PI / 180) + 11, ycord + sin((angle - 90) * constants::PI / 180) + 11, 0.3, angle, 30, constants::BULLET_WIDTH, constants::LASER_HEIGHT);
	}
	
	return bullets;
}
