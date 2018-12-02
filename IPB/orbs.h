#pragma once
#include <SDL.h>
#include "Unit.h"
#include "Player.h"


class Orbs: public Unit
{
public:
	Orbs(SDL_Renderer* renderer, int initialX, int initialY, float scale);
	~Orbs();
	void SetPosition(Player* player);

};