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

//sets position and speed of orbs to that of the player
void orbs::setPosit(Player* player)
{
	position.x = player->GetX()+10;
	position.y = player->GetY()+25;
	this->setSpeed(player->getxSpeed()*1.05, player->getySpeed()*1.05);

}