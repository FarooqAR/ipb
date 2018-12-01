#include "pch.h"
#include "orbs.h"
#include <iostream>
using namespace std;

orbs::orbs(SDL_Renderer * gRenderer, int initialX, int initialY, float scale)
{
	this->objTexture = new LTexture;
	this->objTexture->loadFromFile("assets/bluecirlce.png", gRenderer);
	this->setPosition(initialX, initialY);
	this->renderer = gRenderer;
	this->scale = scale;
	this->alive = true;
	this->destRect = {0, 0, 600, 600};
}

orbs::~orbs()
{

}

/*
void orbs::move1()
{
	speedXdecimal = speedX - floor(speedX);
	speedYdecimal = speedY - floor(speedY);

	//cout << "deltaX" << speedX << "        deltaY" << speedY << "  " << count1 << endl;


	if (speedXdecimal != 0)
	{
		if (count1 %static_cast<int>(1 / speedXdecimal) == 0)
			position.x += 1 * (speedXdecimal / abs(speedXdecimal));
	}
	if (speedYdecimal != 0)
	{
		if (count1%static_cast<int>(1 / speedYdecimal) == 0)
			position.y += 1 * (speedYdecimal / abs(speedYdecimal));
	}

	count1++;

	position.x = position.x + speedX;
	position.y = position.y + speedY;
}
*/

void orbs::setPosit(Player* player)
{
	position.x = player->GetX();
	position.y = player->GetY();
//	cout << player->getxSpeed() << " " << player->getySpeed() << endl;
	this->setSpeed(player->getxSpeed()*1.05, player->getySpeed()*1.05);

}