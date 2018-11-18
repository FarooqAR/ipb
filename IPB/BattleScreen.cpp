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
	backgroundTexture->loadFromFile("assets/space.jpg", renderer);
	healthBarTexture->loadFromFile("assets/health.png", renderer);
	fuelBarTexture->loadFromFile("assets/fuel.png", renderer);
	oxygenBarTexture->loadFromFile("assets/oxygen.png", renderer);

	hero = new Player(renderer, 490, 500);
	planets.enqueue(new Attractor(renderer, 0.0, 0.0, "assets/mercury.png", 100, 100, 0.4));
	planets.enqueue(new Attractor(renderer, 0.0, 0.0, "assets/venus.png", 500, 140, 0.45));
	planets.enqueue(new Attractor(renderer, 0.0, 0.0, "assets/mars.png", 900, 210, 0.35));
	planets.enqueue(new Attractor(renderer, 0.0, 0.0, "assets/earth.png", 240, 290, 0.5));
	planets.enqueue(new Attractor(renderer, 0.0, 0.0, "assets/jupiter.png", 590, 300, 0.57));
	planets.enqueue(new Attractor(renderer, 0.0, 0.0, "assets/uranus.png", 200, 590, 0.47));
	planets.enqueue(new Attractor(renderer, 0.0, 0.0, "assets/neptune.png", 700, 530, 0.49));
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
		healthBarTexture->renderTexture(900 + i, 700, renderer);
		i += 1;
	}
	i = 0;
	while (i < hero->getOxygen())
	{
		oxygenBarTexture->renderTexture(900 + i, 715, renderer);
		i += 1;
	}
	i = 0;
	while (i < hero->getFuel())
	{
		fuelBarTexture->renderTexture(900 + i, 730, renderer);
		i += 1;
	}
	planets.render();
	bool isColliding = planets.checkCollision(hero);
	// toggle ship color when it collides
	if (isColliding && frames % 20 == 0)
	{
		if (hero->getCurrentClipIndex() == 1)
			hero->setCurrentClipIndex(2);
		else
			hero->setCurrentClipIndex(1);
	}
	else if (!isColliding)
	{
		hero->setCurrentClipIndex(0);
	}
	planets.clean();
	if (hero->getAlive())
	{
		hero->render();
		hero->move();
	}
	else
	{
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
	}

	if (currentKeyStates[SDL_SCANCODE_DOWN])
	{
		hero->move(DOWN);
	}
}
