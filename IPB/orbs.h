#pragma once
#include <SDL.h>
#include "Unit.h"
#include "Player.h"


class orbs: public Unit
{
public:
	orbs(SDL_Renderer* renderer, int initialX, int initialY, float scale);
	~orbs();
	//void move1();
	void setPosit(Player* player);

private:

};