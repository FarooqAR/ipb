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
	float oxygen;
	float fuel;;
	Weapon * weapons; 
	bool isThrusting;
	SDL_Rect shipSpriteClips[11];
	int shipCurrentClipIndex;
	int ShootDelay;
	int Ammo;
public:
	~Player(); 
	Bullet* Shoot(SDL_Renderer* gRenderer, LTexture*);
	Player(SDL_Renderer*, LTexture*, int, int, float Angle = 0);
	void SetAmmo(int);
	void SetDelay(int);
	int GetDelay();
	int GetAmmo();
	void render();
	void setHealth(float);
	void setOxygen(float);
	void setFuel(float);
	void setShipCurrentClipIndex(int);
	void changeShipCurrentClipIndex();
	float getHealth();
	float getOxygen();
	float getFuel();
	int getCurrentClipIndex();
	bool getIsThrusting();
	void setIsThrusting(bool);
	int GetX();
	int GetY();
	Weapon* GetWeapon();
	void SetWeapon(Weapon*);
};
