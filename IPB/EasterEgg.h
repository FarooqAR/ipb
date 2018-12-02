#pragma once

#include "Unit.h"
#include "Player.h"
#include "LTexture.h"
#include "constants.h"
#include "Weapon.h"


/*PowerUps that the player can collect to boost one of their attributes, i.e. Health, Fuel, Oxygen, Weapon Type.
Disappear after a short while. 
*/

class EasterEgg : public Unit
{
	private:
		const char* name;
		bool disappear;
		int type;
	public:
		EasterEgg();
		EasterEgg(SDL_Renderer* gRenderer, LTexture*, int Type);
		~EasterEgg();
		void HasCollected(Player * player);
		void move();
};