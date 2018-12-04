#pragma once
#include "Unit.h"
#include "LTexture.h"

class Bullet : public Unit
{
	private:
		const char * name;

	public:
		Bullet();
		~Bullet();
		virtual void Move();
		Bullet(SDL_Renderer* gRenderer, LTexture*, int bulletType, int x, int y, float scale, double angle, int damage, int bulletWidth, int bulletHeight);
};
