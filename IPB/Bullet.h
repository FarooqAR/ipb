#pragma once

#include "Unit.h"

class Bullet : public Unit
{
private:
	const char * name;
	LTexture * bulletTexture;
	int damage;
public:
	Bullet();
	~Bullet();
};
