#pragma once
#include "Player.h"
#include "Attractor.h"
#include "EasterEgg.h"

class Level
{
public:
	Level();
	~Level();

private:
	const char* levelName;
	int levelIndex;
	Player* enemy;
	Attractor* planets;
	EasterEgg* easterEggs;
};

