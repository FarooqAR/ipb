#include "Unit.h"
#include "TextureManager.h"
#include <math.h>

Unit::Unit(const char* textureSheet, SDL_Renderer* ren, int x, int y)
{
	pos.x = x;
	pos.y = y;
	renderer = ren;
	objTexture = TextureManager::LoadTexture(textureSheet, ren);
	/*srcRect.w = 28;
	srcRect.h = 64;
	srcRect.x = 0;
	srcRect.y = 0;*/
}
Point Unit::getPos()
{
	return pos;
}
void Unit::setPos(int x, int y)
{
	pos.x = x;
	pos.y = y;
}

void Unit::update()
{
	destRect.x = pos.x;
	destRect.y = pos.y;
	destRect.w = 28;
	destRect.h = 64;

}
void Unit::render()
{
	SDL_RenderCopy(renderer, objTexture, NULL, &destRect);
}