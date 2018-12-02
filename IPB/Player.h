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
	Weapon * weapon; 
	bool isThrusting;
	SDL_Rect shipSpriteClips[11];
	int shipCurrentClipIndex;
	int shootDelay;
	int ammo;
public:
	~Player(); 
	Bullet* Shoot(SDL_Renderer* gRenderer, LTexture*);
	Player(SDL_Renderer*, LTexture*, int, int, float Angle = 0);
	void SetAmmo(int);
	void SetDelay(int);
	int GetDelay();
	int GetWeaponDelay();
	int GetAmmo();
	string GetWeaponName();
	int GetWeaponType();
	void SetWeaponType(int);
	void Render();
	void SetHealth(float);
	void SetOxygen(int);
	void SetFuel(int);
	void SetShipCurrentClipIndex(int);
	void ChangeShipCurrentClipIndex();
	float GetHealth();
	int GetOxygen();
	int GetFuel();
	int GetCurrentClipIndex();
	bool GetIsThrusting();
	void SetIsThrusting(bool);
	int GetX();
	int GetY();
};
