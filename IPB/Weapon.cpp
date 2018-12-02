#include "pch.h"
#include "constants.h"
#include "Weapon.h"
#include "Game.h"
#include <cmath>


//Constructors
Weapon::Weapon()
{
	bullets = nullptr;
	WeaponType = constants::SIMPLE_BULLET;
	TimeDelay = 30;
	Ammo = 30;
}


Weapon::Weapon(int delay, int type, int ammo)
{
	bullets = nullptr;
	this->name = name;
	WeaponType = type;
	TimeDelay = delay;
	Ammo = ammo;
}

//Destructor
Weapon::~Weapon()
{
	delete bullets;
}

/*Getters*/

int Weapon::GetDelay()
{
	return TimeDelay;
}

const char* Weapon::GetWeaponName()
{
	if (GetWeaponType() == constants::SIMPLE_BULLET)
		return "Gun";
	else if (GetWeaponType() == constants::MISSILE)
		return "Launcher";
	return "Laser";
}

int Weapon::GetWeaponType()
{
	return WeaponType;
}
int Weapon::GetAmmo()
{
	return Ammo;
}

/*Setters*/

void Weapon::SetWeaponType(int weaponType)
{
	this->WeaponType = weaponType;
}

void Weapon::setWeaponName(const char * w_name)
{
	name = w_name;
}



//creates a bullet object to shoot
Bullet* Weapon::Fire(SDL_Renderer* gRenderer, LTexture* imagesSpriteSheet, int xcord, int ycord, double angle)
{
	if (WeaponType == constants::SIMPLE_BULLET)
	{
		bullets = new Bullet(gRenderer, imagesSpriteSheet, WeaponType, (int)(xcord + cos((angle - 90) * constants::PI / 180) + 11), (int)(ycord + sin((angle - 90) * constants::PI / 180) + 11), 0.15f, angle, 10, constants::BULLET_WIDTH, constants::BULLET_HEIGHT);
	}

	if (WeaponType == constants::MISSILE)
	{
		bullets = new Bullet(gRenderer, imagesSpriteSheet, WeaponType, (int)(xcord + cos((angle - 90) * constants::PI / 180) + 11), (int)(ycord + sin((angle - 90) * constants::PI / 180) + 11), 0.3f, angle, 20, constants::BULLET_WIDTH, constants::MISSILE_HEIGHT);
	}

	if (WeaponType == constants::LASER)
	{
		bullets = new Bullet(gRenderer, imagesSpriteSheet, WeaponType, (int)(xcord + cos((angle - 90) * constants::PI / 180) + 11), (int)(ycord + sin((angle - 90) * constants::PI / 180) + 11), 0.3f, angle, 30, constants::BULLET_WIDTH, constants::LASER_HEIGHT);
	}
	Game::getInstance()->PlayMusic(constants::MUSIC_BULLET);
	return bullets;
}
