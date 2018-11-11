#pragma once

#include "Unit.h"
// each easter egg (elon musk etc) will have some amount of given attributes which will
// be transferred to the spaceship once it reaches it
class EasterEgg : public Unit
{
private:
	const char* name;
	int health;
	int oxygen;
	int fuel;
	int ammo;
	int weapon;
public:
	EasterEgg();
	~EasterEgg();
};