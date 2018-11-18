#pragma once
#include "Unit.h" 
#include "Weapon.h" 
#include <SDL.h>

class Player : public Unit
{
private:
	int health;
	int oxygen;
	int fuel;
	int mass; // 0 for enemy
	Weapon * weapons; 
	SDL_Rect spriteClips[3];
	int currenClipIndex;
public:
	Player(SDL_Renderer*, int, int);
	~Player(); 
	void render(); 
	void setHealth(int);
	void setOxygen(int);
	void setFuel(int);
	void setCurrentClipIndex(int);
	int getHealth();
	int getOxygen();
	int getFuel();
	int getCurrentClipIndex();
};