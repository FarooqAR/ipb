#pragma once
#include "Unit.h" 
#include "Bullet.h" 
#include "LTexture.h"

class Weapon : public Unit
{
private:
	const char* name;
	LTexture * weaponTexture;
	Bullet * bullets;
public:
	// constructors and destructor
	// all getters and setters
};