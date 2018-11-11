#pragma once
#include "Unit.h"
#include "Weapon.h"
#include "Attractor.h"
#include "EasterEgg.h"
#include "Bullet.h"

class UnitFactory
{
private:
	UnitFactory();
public:
	UnitFactory * getInstance();
	Attractor * createPlanet(int x, int y, int gravity, int planetType);
	Weapon * createWeapon(int x, int y, int weaponType);
	Unit * createAsteroid(int x, int y, int asteroidType, int speed);
	EasterEgg * createEasterEgg(int x, int y, int easterEggType);
	Bullet * createBullet(int x, int y, int bulletType, int speed);
};