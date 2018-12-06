#pragma once
#include "Unit.h"
#include "constants.h"

//Randomly generated obstructions that will hinder the pathway of the player OR enemy

class Asteroid : public Unit
{
	public:
		Asteroid();
		Asteroid(SDL_Renderer* gRenderer, LTexture* imageSpriteSheet, float scale, int damage = 20, int speedX = 4, int speedY = 4);
		void Move();
		~Asteroid();
	private:
		int damage;
		char direction;
		void SetPosition();
};

