#include "pch.h"
#include "orbs.h"
#include <iostream>
using namespace std;

/*Guide used to indicate the direction of the gravitational force pulling the player*/

orbs::orbs(SDL_Renderer * gRenderer, int initialX, int initialY, float scale)
{
	this->objTexture = new LTexture;
	this->objTexture->LoadFromFile("assets/bluecirlce.png", gRenderer);
	((Unit*)this)->SetPosition(initialX, initialY);
	this->renderer = gRenderer;
	this->scale = scale;
	this->alive = true;
	this->destRect = {0, 0, 600, 600};
}

Orbs::~Orbs()
{

}

//sets position and speed of orbs to that of the player
void Orbs::SetPosition(Player* player)
{
	position.x = player->GetX()+10;
	position.y = player->GetY()+25;
	this->SetSpeed(player->GetXSpeed()*1.05f, player->GetYSpeed()*1.05f);

}