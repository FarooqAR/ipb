#pragma once
#include "Unit.h"
#include "Player.h"
#include "LTexture.h"
#include "Point.h"
#include "Gravity.h"

class Attractor : public Unit
{
private:
	Gravity pull;
	float gravConstant = 2;
	int planetType;
public:
	Attractor();
	Attractor(SDL_Renderer* gRenderer, LTexture* planetsTexture, int planetType, int x, int y, float scale);
	~Attractor();
	void gravForce(Unit*);
	int GetPlanetType();
};