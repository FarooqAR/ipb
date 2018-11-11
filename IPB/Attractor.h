#pragma once
#include "Unit.h"
#include "Player.h"

class Attractor :Unit
{
private:
	double mass;
public:
	Attractor();
	~Attractor();
	void gravForce(Player*);
};