#pragma once
#include "Unit.h"
#include "Player.h"
#include "LTexture.h"
#include "Point.h"

class Attractor : public Unit
{
private:
	double mass;
	double radius;
public:
	Attractor();
	Attractor(SDL_Renderer* gRenderer, double mass, double radius, const char * filename, int x, int y, float scale);
	~Attractor();
	void gravForce(Player*);
};