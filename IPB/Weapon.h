#pragma once
#include "Unit.h" 
#include "Bullet.h" 
#include "LTexture.h"
#include <cmath>


class Weapon : public Unit
{
private:
	const char* name;
	Bullet * bullets;
	int timeDelay;
	int weaponType;
	int ammo;

public:
	Weapon();
	Weapon(int, int, int ammo = 30);
	~Weapon();
	int GetDelay();
	Bullet *  Fire(SDL_Renderer* gRenderer, LTexture*, int, int, double);
	const char* GetWeaponName();
	int GetWeaponType();
	int GetAmmo();
	void SetAmmo(int);
	void SetWeaponType(int);
	void SetWeaponName(const char* w_name);
};
