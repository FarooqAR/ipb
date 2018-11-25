#include "pch.h"
#include "Weapon.h"
#include <cmath>

Weapon::Weapon()
{
	bullets = nullptr;
	name = "Gun";
	WeaponType = 1;
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

int Weapon::GetAmmo()
{
	return Ammo;
}

Bullet* Weapon::Fire(SDL_Renderer* gRenderer, int xcord, int ycord, double angle)
{
	if (WeaponType == 1)
	{
		bullets = new Bullet(gRenderer, "assets/bullet.png", xcord + cos((angle - 90) * M_PI / 180) + 11, ycord + sin((angle - 90) * M_PI / 180) + 11, 0.018, angle, 10);
	}

	if (WeaponType == 2)
	{
		bullets = new Bullet(gRenderer, "assets/missile.png", xcord + cos((angle - 90) * M_PI / 180) + 11, ycord + sin((angle - 90) * M_PI / 180) + 11, 0.018, angle, 20);
	}

	if (WeaponType == 3)
	{
		bullets = new Bullet(gRenderer, "assets/laser.png", xcord + cos((angle - 90) * M_PI / 180) + 11, ycord + sin((angle - 90) * M_PI / 180) + 11, 0.059, angle, 30);
	}
	
	return bullets;
}
