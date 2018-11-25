#include "pch.h"
#include "BattleScreen.h"
#include "LTexture.h"
#include "Queue.h"
#include <iostream>
#include "Attractor.h"
#include "Unit.h"
#include "Player.h"
#include "Game.h"

using namespace std;

BattleScreen::BattleScreen(SDL_Renderer* renderer) : renderer(renderer)
{
	frames = 0;
	backgroundTexture = new LTexture;
	healthBarTexture = new LTexture;
	oxygenBarTexture = new LTexture;
	fuelBarTexture = new LTexture;
	explosionTexture = new LTexture;
	backgroundTexture->loadFromFile("assets/space.jpg", renderer);
	healthBarTexture->loadFromFile("assets/health.png", renderer);
	fuelBarTexture->loadFromFile("assets/fuel.png", renderer);
	oxygenBarTexture->loadFromFile("assets/oxygen.png", renderer);
	explosionTexture->loadFromFile("assets/explosion.png", renderer);

	hero = new Player(renderer, constants::WINDOW_WIDTH / 2, constants::WINDOW_HEIGHT - 100);
	planets.enqueue(new Attractor(renderer, "assets/mercury.png", 100, 550, 0.4));
	planets.enqueue(new Attractor(renderer, "assets/venus.png", 500, 140, 0.45));
	planets.enqueue(new Attractor(renderer, "assets/mars.png", 750, 310, 0.35));
	planets.enqueue(new Attractor(renderer, "assets/earth.png", 195, 140, 0.5));
	planets.enqueue(new Attractor(renderer, "assets/jupiter.png", 400, 400, 0.57));
	planets.enqueue(new Attractor(renderer, "assets/neptune.png", 700, 530, 0.49));
	for (int i = 0; i < 20; i++)
	{
		explosionSpriteClips[i] = { 96 * i, 0, 96, 96 };
	}
}
BattleScreen::~BattleScreen()
{
	delete backgroundTexture;
	delete healthBarTexture;
	delete oxygenBarTexture;
	delete fuelBarTexture;
}
void BattleScreen::render()
{
	backgroundTexture->renderTexture(0, 0, renderer);
	int i = 0;
	while (i < hero->getHealth())
	{
		healthBarTexture->renderTexture(constants::WINDOW_WIDTH - 130 + i, constants::WINDOW_HEIGHT - 50, renderer);
		i += 1;
	}
	i = 0;
	while (i < hero->getOxygen())
	{
		oxygenBarTexture->renderTexture(constants::WINDOW_WIDTH - 130 + i, constants::WINDOW_HEIGHT - 35, renderer);
		i += 1;
	}
	i = 0;
	while (i < hero->getFuel())
	{
		fuelBarTexture->renderTexture(constants::WINDOW_WIDTH - 130 + i, constants::WINDOW_HEIGHT - 20, renderer);
		i += 1;
	}
	planets.render();
	bool isColliding = planets.checkCollision(hero);
	// toggle ship color when it collides
	if (isColliding)
	{
		if (frames % 20 == 0)
		{
			if (hero->getIsThrusting())
			{
				if (hero->getCurrentClipIndex() == 9)
					hero->setShipCurrentClipIndex(10);
				else
					hero->setShipCurrentClipIndex(9);
			}
			else
			{

				if (hero->getCurrentClipIndex() == 1)
					hero->setShipCurrentClipIndex(2);
				else
					hero->setShipCurrentClipIndex(1);
			}
		}
	}
	else
	{
		if (hero->getIsThrusting())
		{
			if (frames % 3 == 0)
				hero->changeShipCurrentClipIndex();

		}
		else
		{
			hero->setShipCurrentClipIndex(0);

		}
	}
	planets.clean();
	if (hero->getAlive())
	{
		hero->render();
	}
	else
	{
		explosionTexture->renderTexture(
			hero->getPosition().x + hero->getWidth() / 2 - 96 / 2,
			hero->getPosition().y + hero->getHeight() / 2 - 96 / 2,
			renderer,
			&explosionSpriteClips[explosionSpriteIndex]
		);
		if (frames % 4 == 0)
			explosionSpriteIndex++;
		if (explosionSpriteIndex == 19)
			Game::setCurrentScreen(constants::GAME_OVER_SCREEN);
	}

	frames++;

}
void BattleScreen::handleEvents(SDL_Event& event)
{
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_RIGHT])
	{
		hero->move(RIGHT);
	}

	if (currentKeyStates[SDL_SCANCODE_LEFT])
	{
		hero->move(LEFT);
	}

	if (currentKeyStates[SDL_SCANCODE_UP])
	{
		hero->move(UP);
		hero->setIsThrusting(true);
	}
	else
	{
		hero->setIsThrusting(false);
		planets.pull(hero);
		hero->move();
	}


}
