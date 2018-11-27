#pragma once
#include "Unit.h"
#include "LTexture.h"

class Bullet : public Unit
{
	private:
		const char * name;
		int damage;

	public:
		Bullet();
		~Bullet();
		virtual void move();
		Bullet(SDL_Renderer* gRenderer, LTexture*, int x, int y, float scale, double angle, int damage);
};
