#pragma once
#include "Unit.h" 
#include "Weapon.h" 
#include "Gravity.h"
#include "LTexture.h"
#include "Bullet.h"
#include <SDL.h>

class Player : public Unit
{
private:
	float health;
	int oxygen;
	int fuel;;
	Weapon * weapons; 
	bool isThrusting;
	SDL_Rect shipSpriteClips[3];
	int shipCurrentClipIndex;
	int ShootDelay;
	int Ammo;
public:
	~Player(); 
	Bullet* Shoot(SDL_Renderer* gRenderer, LTexture*);
	Player(SDL_Renderer*, int, int, float Angle = 0);
	void SetAmmo(int);
	void SetDelay(int);
	int GetDelay();
	int GetWeaponDelay();
	int GetWeaponAmmo();
	int GetAmmo();
	string GetWeaponName();
	int GetWeaponType();
	void render();
	void setHealth(float);
	void setOxygen(int);
	void setFuel(int);
	void setShipCurrentClipIndex(int);
	void changeShipCurrentClipIndex();
	float getHealth();
	int getOxygen();
	int getFuel();
	int getCurrentClipIndex();
	bool getIsThrusting();
	void setIsThrusting(bool);
	int GetX();
	int GetY();
};
