#pragma once
#include "Unit.h" 
#include "Weapon.h" 
#include "Gravity.h"
#include "LTexture.h"
#include <SDL.h>

class Player : public Unit
{
private:
	float health;
	int oxygen;
	int fuel;
	bool isThrusting;
	Weapon * weapons; 
	SDL_Rect shipSpriteClips[3];
	int shipCurrentClipIndex;
public:
	//capital
	Player(SDL_Renderer*, int, int);
	~Player(); 
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
};