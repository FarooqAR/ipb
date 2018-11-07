#pragma once

#include "Unit.h" 
#include "Weapon.h" 

class Player : public Unit
{
private:
	int velocity;
	int health;
	int oxygen;
	int fuel;
	int mass; // 0 for enemy
	Weapon * weapons; 
public:
	// constructors and destructor
	// all getters and setters
};