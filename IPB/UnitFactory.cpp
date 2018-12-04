#include "pch.h"
#include "UnitFactory.h"
#include "constants.h"
#include "Attractor.h"
#include "LTexture.h"
#include "EasterEgg.h"


UnitFactory* UnitFactory::instance = nullptr;
UnitFactory::UnitFactory(SDL_Renderer* gRenderer)
	:gRenderer(gRenderer)
{

}
UnitFactory * UnitFactory::getInstance(SDL_Renderer* gRenderer)
{
	if (instance == nullptr)
		instance = new UnitFactory(gRenderer);
	return instance;
}

Attractor * UnitFactory::CreatePlanet(LTexture* imageSpriteSheet, int planetType, int x, int y, float scale)
{
	return new Attractor(gRenderer, imageSpriteSheet, planetType, x, y, scale);
}

Weapon * UnitFactory::CreateWeapon(int delay, int weaponType, int ammo)
{
	return new Weapon(delay, weaponType, ammo);
}


Bullet * UnitFactory::CreateBullet(LTexture* imagesSpriteSheet, int weaponType, int x, int y, double angle)
{
	Bullet* bullet = nullptr;
	if (weaponType == constants::LASER)
	{
		bullet = new Bullet(gRenderer, imagesSpriteSheet, weaponType, (int)(x + cos((angle - 90) * constants::PI / 180) + 11), (int)(y + sin((angle - 90) * constants::PI / 180) + 11), 0.25f, angle, 50, constants::BULLET_WIDTH, constants::LASER_HEIGHT);
	}
	else if (weaponType == constants::MISSILE)
	{
		bullet = new Bullet(gRenderer, imagesSpriteSheet, weaponType, (int)(x + cos((angle - 90) * constants::PI / 180) + 11), (int)(y + sin((angle - 90) * constants::PI / 180) + 11), 0.3f, angle, 7, constants::BULLET_WIDTH, constants::MISSILE_HEIGHT);
	}
	else
	{
		bullet = new Bullet(gRenderer, imagesSpriteSheet, weaponType, (int)(x + cos((angle - 90) * constants::PI / 180) + 11), (int)(y + sin((angle - 90) * constants::PI / 180) + 11), 0.15f, angle, 5, constants::BULLET_WIDTH, constants::BULLET_HEIGHT);
	}
	return bullet;
}

Asteroid * UnitFactory::CreateAsteroid(LTexture* imageSpriteSheet, float scale)
{
	return new Asteroid(gRenderer, imageSpriteSheet, scale);
}

EasterEgg * UnitFactory::CreateEasterEgg(LTexture * imageSpriteSheet, int EggType)
{
	return new EasterEgg(gRenderer, imageSpriteSheet, EggType);
}


