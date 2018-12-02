#include "pch.h"
#include "constants.h"
#include "Attractor.h"
#include "LTexture.h"
#include <cmath>
#include <iostream>

using namespace std;

Attractor::Attractor()
{
}
Attractor::Attractor(SDL_Renderer * gRenderer, LTexture * planetsTexture, int planetType, int x, int y, float scale)
{
	this->setPosition(x, y);
	this->objTexture = planetsTexture;
	this->renderer = gRenderer;
	this->scale = scale;
	this->planetType = planetType;
	this->width = (int) (constants::PLANET_WIDTH * scale);
	this->height = (int) (constants::PLANET_HEIGHT * scale);
	this->destRect = { 
		constants::PLANETS_SPRITE_START_POSITION.x + 200 * planetType, 
		constants::PLANETS_SPRITE_START_POSITION.y, 
		constants::PLANET_WIDTH, 
		constants::PLANET_HEIGHT 
	};
}

Attractor::~Attractor()
{
}

void Attractor::gravForce(Unit* player)
{
	int playerX = player->getPosition().x;
	int playerY = player->getPosition().y;

	pull.x = 0;
	pull.y = 0;
	//calculates the pull of gravity
	if ((playerX - position.x != 0) && (playerY - position.y != 0))
	{
		pull.x = (float)(-(playerX - position.x) / pow(sqrt(pow((playerX - position.x), 2) + pow((playerY - position.y), 2)), 2));
		pull.y = (float)(-(playerY - position.y) / pow(sqrt(pow((playerX - position.x), 2) + pow((playerY - position.y), 2)), 2));
	}
	
	//applies gravitational constant 
	pull.x *= gravConstant;
	pull.y *= gravConstant;

	// adds the gravity to the speed
	float speedx = player->getxSpeed();
	float speedy = player->getySpeed();
	player->setSpeed(speedx + pull.x, speedy + pull.y);
}

int Attractor::GetPlanetType()
{
	return planetType;
}
