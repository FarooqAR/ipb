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
	float gravConstant = 1;
public:
	Attractor();
	Attractor(SDL_Renderer* gRenderer, const char * filename, int x, int y, float scale);
	~Attractor();
	void gravForce(Player*);
};