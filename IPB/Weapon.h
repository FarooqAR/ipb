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
	int TimeDelay;
	int WeaponType;
	int Ammo;

public:
	Weapon();
	Weapon(int, int, int ammo = 30);
	~Weapon();
	int GetDelay();
	Bullet *  Fire(SDL_Renderer* gRenderer, LTexture*, int, int, double);
	const char* GetWeaponName();
	int GetWeaponType();
	int GetAmmo();
	void SetWeaponType(int);
	void setWeaponName(const char* w_name);
};
