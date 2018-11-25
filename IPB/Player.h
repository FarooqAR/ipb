#pragma once
#include "Unit.h" 
#include "Weapon.h" 
#include "Gravity.h"
#include "LTexture.h"
#include <SDL.h>

class Player : public Unit
{
private:
	int health;
	int oxygen;
	int fuel;
	int mass; // 0 for enemy
	Weapon * weapons; 
	SDL_Rect shipSpriteClips[3];
	int shipCurrentClipIndex;
public:
	//capital
	Player(SDL_Renderer*, int, int);
	~Player(); 
	void render(); 
	void setHealth(int);
	void setOxygen(int);
	void setFuel(int);
	void setShipCurrentClipIndex(int);
	void GetPulled();
	int getHealth();
	int getOxygen();
	int getFuel();
	int getCurrentClipIndex();

};