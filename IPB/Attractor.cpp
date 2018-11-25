#include "pch.h"
#include "Attractor.h"
#include "LTexture.h"
#include <cmath>
#include <iostream>

using namespace std;

Attractor::Attractor()
{
	// hello world;
}

Attractor::Attractor(SDL_Renderer* gRenderer, const char * filename, int x, int y, float scale)
{
	this->setPosition(x, y);
	this->objTexture = new LTexture;
	this->renderer = gRenderer;
	this->scale = scale;
	this->objTexture->loadFromFile(filename, gRenderer);
	this->width = this->objTexture->getWidth() * scale;
	this->height = this->objTexture->getHeight() * scale;
}

void Attractor::gravForce(Player* player)
{
	int playerX = player->getPosition().x;
	int playerY = player->getPosition().y;

	pull.x = -(playerX - position.x) / pow(sqrt(pow((playerX - position.x), 2) + pow((playerY - position.y), 2)), 2);
	pull.y = -(playerY - position.y) / pow(sqrt(pow((playerX - position.x), 2) + pow((playerY - position.y), 2)), 2);

	pull.x *= gravConstant;
	pull.y *= gravConstant;

	player->speedX = player->speedX + pull.x;
	player->speedY = player->speedY + pull.y;
}
