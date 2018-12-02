#include "pch.h"
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include "Game.h"
#include "constants.h"
#include "BattleScreen.h"
#include <fstream>
#include<cstdlib>
#include <time.h>


using namespace std;

Game * game = nullptr;


int main(int argc, char* args[])
{
	srand(time(0));
	const int FPS = 60;
	const int frameDelay = 1000 / FPS; // optimal time taken for a single frame
	Uint32 frameStart;
	int frameTime;
	game = Game::getInstance();
	game->init("Interplanetary Battlefield", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, constants::WINDOW_WIDTH, constants::WINDOW_HEIGHT, false);
	while (game->running())
	{
		frameStart = SDL_GetTicks(); // milliseconds since the program started
		game->handleEvents();
		game->update();
		game->render();
		frameTime = SDL_GetTicks() - frameStart; // time took for one frame
		// if a single frame is took less time (than the optimal one) to render,
		// then put a little delay before rendering the next frame so it appears smooth 
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	return 0;
}