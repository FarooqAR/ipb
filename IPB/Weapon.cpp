#include "pch.h"
#include "constants.h"
#include "Weapon.h"
#include "Game.h"
#include <cmath>


Weapon::Weapon()
{
	weaponType = constants::SIMPLE_BULLET;
	timeDelay = 60;
	ammo = 30;
	damage = 5;
}

Weapon::Weapon(int delay, int type, int ammo)
{
	this->name = name;
	timeDelay = delay;
	this->ammo = ammo;	
	this->SetWeaponType(type);
}

Weapon::~Weapon()
{
	
}


int Weapon::GetDelay()
{
	return timeDelay;
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
	return weaponType;
}
int Weapon::GetDamage()
{
	return damage;
}
int Weapon::GetAmmo()
{
	return ammo;
}

void Weapon::SetAmmo(int a)
{
	this->ammo = a;
}

/*Setters*/

void Weapon::SetWeaponType(int weaponType)
{
	int damages[3] = { 5, 10, 15 };
	this->weaponType = weaponType;
	this->damage = damages[weaponType];
}

void Weapon::SetWeaponName(const char * w_name)
{
	name = w_name;
}

//creates a bullet object to shoot
Bullet* Weapon::Fire(SDL_Renderer* gRenderer, LTexture* imagesSpriteSheet, int xcord, int ycord, double angle)
{
	Game::GetInstance()->PlayMusic(constants::MUSIC_BULLET);
	return Game::GetInstance()->GetUnitFactory()->CreateBullet(imagesSpriteSheet, weaponType, xcord, ycord, angle);
}
