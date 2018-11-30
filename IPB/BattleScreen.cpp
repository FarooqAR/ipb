#include "pch.h"
#include "BattleScreen.h"
#include "LTexture.h"
#include "Queue.h"
#include "Word.h"
#include "Attractor.h"
#include "Unit.h"
#include "Player.h"
#include "Game.h"
#include "Enemy.h"
#include "Button.h"
#include "Word.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <string>

using namespace std;

BattleScreen::BattleScreen(SDL_Renderer* renderer, int h, int w, float angle) : renderer(renderer)
{
	frames = 0;

	explosionTexture = new LTexture;
	backgroundTexture = new LTexture;
	healthBarTexture = new LTexture;
	oxygenBarTexture = new LTexture;
	fuelBarTexture = new LTexture;
	explosionTexture = new LTexture;
	bulletTexture = new LTexture;
	buttonSpriteSheet = new LTexture;
	alphabetsSpriteSheet = new LTexture;
	wormHoleTexture = new LTexture;
	alphabetsSpriteSheet->loadFromFile("assets/spries.png", renderer, 1, 0, 0, 0);
	buttonSpriteSheet->loadFromFile("assets/button_sprite.png", renderer);
	backgroundTexture->loadFromFile("assets/space.jpg", renderer);
	healthBarTexture->loadFromFile("assets/health.png", renderer);
	fuelBarTexture->loadFromFile("assets/fuel.png", renderer);
	oxygenBarTexture->loadFromFile("assets/oxygen.png", renderer);
	explosionTexture->loadFromFile("assets/explosion.png", renderer);
	bulletTexture->loadFromFile("assets/bullet.png", renderer);
	wormHoleTexture->loadFromFile("assets/wormhole.png", renderer);
	wormHole = new Unit(renderer, wormHoleTexture, 0, 0, 0);
	wormHole->setPosition(100, 300);

	hero = new Player(renderer, constants::WINDOW_WIDTH / 2, constants::WINDOW_HEIGHT - 100);
	enemy = new Enemy(renderer, constants::WINDOW_WIDTH - 200, 30);
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
	alphabetsSpriteSheet->loadFromFile("assets/spries.png", renderer, 1, 0, 0, 0);

	string title = "Weapon: " + hero->GetWeaponName();
	WeaponTitle = new Word(title, alphabetsSpriteSheet, 20, constants::WINDOW_HEIGHT - 50, 0.27);
	title = "Ammo: " + to_string(hero->GetAmmo());
	AmmoCount = new Word(title, alphabetsSpriteSheet, 20, constants::WINDOW_HEIGHT - 25, 0.27);
	enemyHealthBoundary = { 0, 0, 95, 10 };
	heroHealthBoundary = { constants::WINDOW_WIDTH - 130, constants::WINDOW_HEIGHT - 50, 105, 10 };
	heroOxygenBoundary = { constants::WINDOW_WIDTH - 130, constants::WINDOW_HEIGHT - 35, 105, 10 };
	heroFuelBoundary = { constants::WINDOW_WIDTH - 130, constants::WINDOW_HEIGHT - 20, 105, 10 };
}

BattleScreen::~BattleScreen()
{
	delete backgroundTexture;
	delete healthBarTexture;
	delete oxygenBarTexture;
	delete fuelBarTexture;
	delete alphabetsSpriteSheet;
}

void BattleScreen::render()
{
	backgroundTexture->renderTexture(0, 0, renderer);
	WeaponTitle->render(renderer);
	AmmoCount->render(renderer);
	enemyHealthBoundary.x = enemy->getPosition().x;
	enemyHealthBoundary.y = enemy->getPosition().y - 10;
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 1);
	if (enemy->getAlive())
		SDL_RenderDrawRect(renderer, &enemyHealthBoundary);
	SDL_RenderDrawRect(renderer, &heroHealthBoundary);
	SDL_SetRenderDrawColor(renderer, 88, 180, 180, 1);
	SDL_RenderDrawRect(renderer, &heroOxygenBoundary);
	SDL_SetRenderDrawColor(renderer, 228, 123, 36, 1);
	SDL_RenderDrawRect(renderer, &heroFuelBoundary);
	if (!enemy->getAlive() && hero->getAlive())
	{
		wormHole->setAngle(wormHole->getAngle() - 0.2);
		if (!intoWormHole)
		{
			wormHole->setScale(wormHole->getScale() + 0.1);
		}
		else
		{
			hero->setScale(hero->getScale() - 0.1);
		}
		if (wormHole->checkCollision(hero, true))
		{
			intoWormHole = true;
		}
		wormHole->render();
	}
	if (enemy->getAlive() && hero->checkCollision(enemy))
	{
		hero->setHealth(0);
		enemy->setHealth(0);
	}
	if (enemy->getAlive() && PlayerBulletQueue.checkCollision(enemy, true))
	{
		enemy->setHealth(enemy->getHealth() - 5);
		PlayerBulletQueue.clean();
	}
	if (EnemyBulletQueue.checkCollision(hero, true))
	{
		hero->setHealth(hero->getHealth() - 5);
		EnemyBulletQueue.clean();
	}

	PlayerBulletQueue.render();
	EnemyBulletQueue.render();
	PlayerBulletQueue.move();
	EnemyBulletQueue.move();

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
	i = 0;
	while (i < enemy->getHealth())
	{
		healthBarTexture->renderTexture(enemy->getPosition().x + i * 0.9, enemy->getPosition().y - 10, renderer);
		i += 1;
	}

	planets.render();

	bool isColliding = planets.checkCollision(hero);
	// toggle ship color when it collides
	if (isColliding)
	{
		hero->setHealth(hero->getHealth() - 0.1);
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
	if (enemy->getAlive() && hero->getAlive())
	{
		if (frames % 50 == 0)
		{
			Bullet *bullet = enemy->getWeapon()->Fire(
				renderer,
				bulletTexture,
				enemy->getPosition().x + enemy->getWidth() / 2,
				enemy->getPosition().y + enemy->getHeight() / 2,
				atan2(
					hero->getPosition().x + hero->getWidth() / 2 - enemy->getPosition().x - enemy->getWidth() / 2,
					enemy->getPosition().y + enemy->getHeight() / 2 - hero->getPosition().y - hero->getHeight() / 2
				) * 180 / M_PI
			);
			EnemyBulletQueue.enqueue(bullet);
		}

	}
	if (enemy->getAlive())
		enemy->render();
	else if (enemExplosionSpriteIndex < 20)
	{
		explosionTexture->renderTexture(
			enemy->getPosition().x + enemy->getWidth() / 2 - 100 / 2,
			enemy->getPosition().y + enemy->getHeight() / 2 - 63 / 2,
			renderer,
			&explosionSpriteClips[enemExplosionSpriteIndex]
		);
		if (frames % 4 == 0)
			enemExplosionSpriteIndex++;
	}
	if (hero->getAlive())
	{
		if (hero->getScale() > 0.1)
			hero->render();
		else
			Game::setCurrentScreen(constants::SELECT_LEVEL_SCREEN);
	}
	else if (heroExplosionSpriteIndex < 20)
	{
		explosionTexture->renderTexture(
			hero->getPosition().x + hero->getWidth() / 2 - 96 / 2,
			hero->getPosition().y + hero->getHeight() / 2 - 96 / 2,
			renderer,
			&explosionSpriteClips[heroExplosionSpriteIndex]
		);
		if (frames % 4 == 0)
			heroExplosionSpriteIndex++;
		if (heroExplosionSpriteIndex == 19)
			Game::setCurrentScreen(constants::GAME_OVER_SCREEN);
	}

	frames++;
}



void BattleScreen::handleEvents(SDL_Event& event)
{
	int x = 0; int y = 0;

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	hero->SetDelay(hero->GetDelay() + 1);

	if (currentKeyStates[SDL_SCANCODE_RIGHT])
	{
		hero->move(RIGHT);
	}

	if (currentKeyStates[SDL_SCANCODE_LEFT])
	{
		hero->move(LEFT);
	}

	if (currentKeyStates[SDL_SCANCODE_UP] && hero->getAlive())
	{
		hero->move(UP);
		hero->setIsThrusting(true);
	}
	else if (hero->getAlive())
	{
		hero->setIsThrusting(false);
		planets.pull(hero);
		if (!intoWormHole)
			hero->move();
	}

	if (currentKeyStates[SDL_SCANCODE_SPACE])
	{
		if (hero->GetDelay() > hero->GetWeaponDelay() && hero->GetAmmo() > 0 && !intoWormHole)
		{
			Bullet *bullet = hero->Shoot(renderer, bulletTexture);
			PlayerBulletQueue.enqueue(bullet);
			hero->SetDelay(0);
			hero->SetAmmo(hero->GetAmmo() - 1);
			string title = "Ammo: " + to_string(hero->GetAmmo());
			delete AmmoCount;
			AmmoCount = new Word(title, alphabetsSpriteSheet, 20, constants::WINDOW_HEIGHT - 25, 0.27);
		}
	}
	if (currentKeyStates[SDL_SCANCODE_ESCAPE])
	{
		ofstream myfile;
		myfile.open("SavedGame1.txt");
		myfile <<
			hero->getPosition().x << endl <<
			hero->getPosition().y << endl <<
			hero->getAngle() << endl <<
			hero->getHealth() << endl <<
			hero->getOxygen() << endl <<
			hero->getFuel() << endl <<
			hero->GetWeaponType() << endl <<
			2 << endl <<
			hero->GetWeaponAmmo() << endl <<
			hero->GetAmmo() << endl;// <<
			//hero->getCurrentClipIndex() << endl;
		myfile.close();
		//Game::setCurrentScreen(constants::MAIN_MENU_SCREEN);
		Game::setCurrentScreen(constants::PAUSE_SCREEN);

	}
}
