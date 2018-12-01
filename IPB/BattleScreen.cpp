#include "pch.h"
#include <stdio.h>
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
#include "UnitFactory.h"

using namespace std;

BattleScreen::BattleScreen(SDL_Renderer* renderer, UnitFactory* unitFactory, LTexture* imagesSpriteSheet)
	: renderer(renderer)
{
	isPaused = false;
	level = 1;
	frames = 0;
	unitFactory = unitFactory;
	fadeScreenTexture = imagesSpriteSheet;
	explosionTexture = imagesSpriteSheet;
	healthBarTexture = imagesSpriteSheet;
	oxygenBarTexture = imagesSpriteSheet;
	fuelBarTexture = imagesSpriteSheet;
	bulletTexture = imagesSpriteSheet;
	wormHoleTexture = imagesSpriteSheet;

	healthSpriteClip = {
		constants::HEALTH_SPRITE_START_POSITION.x,
		constants::HEALTH_SPRITE_START_POSITION.y,
		constants::STATUS_WIDTH,
		constants::STATUS_HEIGHT
	};
	fuelSpriteClip = {
		constants::HEALTH_SPRITE_START_POSITION.x + constants::STATUS_WIDTH,
		constants::HEALTH_SPRITE_START_POSITION.y,
		constants::STATUS_WIDTH,
		constants::STATUS_HEIGHT
	};
	oxygenSpriteClip = {
		constants::HEALTH_SPRITE_START_POSITION.x + constants::STATUS_WIDTH * 2,
		constants::HEALTH_SPRITE_START_POSITION.y,
		constants::STATUS_WIDTH,
		constants::STATUS_HEIGHT
	};
	pauseScreenSpriteClip = {
		constants::FADE_SCREEN_BG_START_POSITION.x,
		constants::FADE_SCREEN_BG_START_POSITION.y,
		constants::FADE_SCREEN_BG_WIDTH,
		constants::FADE_SCREEN_BG_HEIGHT
	};
	SDL_Rect wormHoleClip = {
		constants::WORMHOLE_SPRITE_START_POSITION.x,
		constants::WORMHOLE_SPRITE_START_POSITION.y,
		constants::WORMHOLE_WIDTH,
		constants::WORMHOLE_HEIGHT
	};
	wormHole = new Unit(renderer, wormHoleTexture, 0, 0, 0);
	wormHole->setPosition(100, 300);
	wormHole->setClip(wormHoleClip);

	hero = new Player(renderer, imagesSpriteSheet, constants::WINDOW_WIDTH / 2, constants::WINDOW_HEIGHT - 100);
	enemy = new Enemy(renderer, imagesSpriteSheet, constants::WINDOW_WIDTH - 200, 30);
	planets.enqueue(unitFactory->createPlanet(imagesSpriteSheet, constants::MERCURY, 100, 550, 0.4f));
	planets.enqueue(unitFactory->createPlanet(imagesSpriteSheet, constants::VENUS, 500, 140, 0.45f));
	planets.enqueue(unitFactory->createPlanet(imagesSpriteSheet, constants::MARS, 750, 310, 0.35f));
	planets.enqueue(unitFactory->createPlanet(imagesSpriteSheet, constants::EARTH, 195, 140, 0.5f));
	planets.enqueue(unitFactory->createPlanet(imagesSpriteSheet, constants::JUPITER, 400, 400, 0.57f));
	planets.enqueue(unitFactory->createPlanet(imagesSpriteSheet, constants::NEPTUNE, 700, 530, 0.49f));

	int x = (constants::WINDOW_WIDTH - constants::BUTTON_WIDTH) / 2;
	ResumeGameBtn = new Button(imagesSpriteSheet, "Resume", x, 200);
	saveGameBtn = new Button(imagesSpriteSheet, "Save Game", x, 200 + 65);
	backBtn = new Button(imagesSpriteSheet, "Back to Menu", x, 200 + 65 * 2);
	quitGameBtn = new Button(imagesSpriteSheet, "Quit", x, 200 + 65 * 3);

	PauseTitle = new Word("Game Paused", imagesSpriteSheet, 0, 300, 1); // 300 here is the starting y coord
	PauseTitle->setXCentered();
	for (int i = 0; i < 20; i++)
	{
		explosionSpriteClips[i] = { constants::EXPLOSION_SPRITE_START_POSITION.x + 96 * i, constants::EXPLOSION_SPRITE_START_POSITION.y, 96, 96 };
	}
	string title = "Weapon: " + hero->GetWeaponName();
	WeaponTitle = new Word(title, imagesSpriteSheet, 20, constants::WINDOW_HEIGHT - 50, 0.27f);
	title = "Ammo: " + to_string(hero->GetAmmo());
	AmmoCount = new Word(title, imagesSpriteSheet, 20, constants::WINDOW_HEIGHT - 25, 0.27f);
	enemyHealthBoundary = { 0, 0, 95, 10 };
	heroHealthBoundary = { constants::WINDOW_WIDTH - 130, constants::WINDOW_HEIGHT - 50, 105, 10 };
	heroOxygenBoundary = { constants::WINDOW_WIDTH - 130, constants::WINDOW_HEIGHT - 35, 105, 10 };
	heroFuelBoundary = { constants::WINDOW_WIDTH - 130, constants::WINDOW_HEIGHT - 20, 105, 10 };
}

BattleScreen::BattleScreen(SDL_Renderer* renderer, UnitFactory* unitFactory, LTexture* imagesSpriteSheet, const char* savedFileName)
	: BattleScreen(renderer, unitFactory, imagesSpriteSheet)
{
	ifstream file(savedFileName);
	string line;
	if (!file || !file.is_open())
		return;
	int i = 1;
	Point pos;
	while (getline(file, line))
	{
		switch (i)
		{
		case 1:
			pos.x = stoi(line);
			break;
		case 2:
			pos.y = stoi(line);
			hero->setPosition(pos.x, pos.y);
			break;
		case 3:
			hero->setAngle(stod(line));
			break;
		case 4:
			hero->setHealth(stof(line));
			break;
		case 5:
			hero->setOxygen(stoi(line));
			break;
		case 6:
			hero->setFuel(stoi(line));
			break;
		case 7:
			//hero->setWeaponName(line.c_str());
			break;
		case 8:
			hero->setWeaponName(line.c_str());
			break;
		case 9:
			hero->SetAmmo(stoi(line));
			break;
		case 10:
			hero->setShipCurrentClipIndex(stoi(line));
			break;
		case 11:
			pos.x = stoi(line);
			break;
		case 12:
			pos.y = stoi(line);
			enemy->setPosition(pos.x, pos.y);
			break;
		case 13:
			enemy->setAngle(stod(line));
			break;
		case 14:
			enemy->setHealth(stof(line));
			break;
		case 15:
			level = stoi(line);
			break;
		default:
			break;
		}
		i++;
		cout << line << '\n';
	}
	file.close();
}
BattleScreen::~BattleScreen()
{

}

void BattleScreen::render()
{
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
			wormHole->setScale(wormHole->getScale() + 0.1f);
		}
		else
		{
			hero->setScale(hero->getScale() - 0.1f);
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

	if (!isPaused)
	{
		PlayerBulletQueue.move();
		EnemyBulletQueue.move();
	}
	PlayerBulletQueue.render();
	EnemyBulletQueue.render();

	int i = 0;
	while (i < hero->getHealth())
	{
		healthBarTexture->renderTexture(constants::WINDOW_WIDTH - 130 + i, constants::WINDOW_HEIGHT - 50, renderer, &healthSpriteClip);
		i += 1;
	}
	i = 0;
	while (i < hero->getOxygen())
	{
		oxygenBarTexture->renderTexture(constants::WINDOW_WIDTH - 130 + i, constants::WINDOW_HEIGHT - 35, renderer, &oxygenSpriteClip);
		i += 1;
	}
	i = 0;
	while (i < hero->getFuel())
	{
		fuelBarTexture->renderTexture(constants::WINDOW_WIDTH - 130 + i, constants::WINDOW_HEIGHT - 20, renderer, &fuelSpriteClip);
		i += 1;
	}
	i = 0;
	while (i < enemy->getHealth())
	{
		healthBarTexture->renderTexture(enemy->getPosition().x + i * 0.9, enemy->getPosition().y - 10, renderer, &healthSpriteClip);
		i += 1;
	}

	planets.render();

	bool isColliding = planets.checkCollision(hero) && !isPaused;
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
	else if(!isPaused)
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
				) * 180 / constants::PI
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

	if (isPaused)
	{
		fadeScreenTexture->renderTexture(25, 50, renderer, &pauseScreenSpriteClip);

		PauseTitle->render(renderer);
		double y = PauseTitle->getY();
		if (PauseTitle->getY() > 100) // handle animation; move the title to y=100
			y = PauseTitle->getY() * 0.9;
		else
		{
			ResumeGameBtn->render(renderer);
			saveGameBtn->render(renderer);
			backBtn->render(renderer);
			quitGameBtn->render(renderer);
		}

		PauseTitle->setPosition(PauseTitle->getX(), y);
	}

	frames++;
}


void BattleScreen::handleEvents(SDL_Event& event)
{
	int x = 0; int y = 0;

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	hero->SetDelay(hero->GetDelay() + 1);

	if (!isPaused)
	{
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
	}
	if (currentKeyStates[SDL_SCANCODE_SPACE] && isPaused == false)
	{
		if (hero->GetDelay() > hero->GetWeaponDelay() && hero->GetAmmo() > 0 && !intoWormHole)
		{
			Bullet *bullet = hero->Shoot(renderer, bulletTexture);
			PlayerBulletQueue.enqueue(bullet);
			hero->SetDelay(0);
			hero->SetAmmo(hero->GetAmmo() - 1);
			string title = "Ammo: " + to_string(hero->GetAmmo());
			AmmoCount->setText(title);
		}
	}
	bool isResumeGameBtnClicked;
	bool isBackBtnClicked;
	bool isQuitGameBtnClicked;
	bool issaveGameBtnClicked;
	switch (event.type)
	{
	case SDL_KEYUP:
		if (event.key.keysym.sym == SDLK_ESCAPE)
			isPaused = !isPaused;
		break;
	case SDL_MOUSEBUTTONDOWN:
		SDL_GetMouseState(&x, &y);
		ResumeGameBtn->onClickDown(x, y);
		saveGameBtn->onClickDown(x, y);
		backBtn->onClickDown(x, y);
		quitGameBtn->onClickDown(x, y);

		break;
	case SDL_MOUSEBUTTONUP:

		SDL_GetMouseState(&x, &y);
		isResumeGameBtnClicked = ResumeGameBtn->onClickUp(x, y);
		issaveGameBtnClicked = saveGameBtn->onClickUp(x, y);
		isBackBtnClicked = backBtn->onClickUp(x, y);
		isQuitGameBtnClicked = quitGameBtn->onClickUp(x, y);
		if (isResumeGameBtnClicked)
			isPaused = false;
		else if (issaveGameBtnClicked)
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
				hero->GetWeaponName() << endl <<
				hero->GetAmmo() << endl <<
				hero->getCurrentClipIndex() << endl <<
				enemy->getPosition().x << endl <<
				enemy->getPosition().y << endl <<
				enemy->getAngle() << endl <<
				enemy->getHealth() << endl <<
				level << endl;// <<
				//hero->getCurrentClipIndex() << endl;

			myfile.close();
		}
		else if (isBackBtnClicked)
			Game::setCurrentScreen(constants::MAIN_MENU_SCREEN);
		else if (isQuitGameBtnClicked)
			exit(0);
		break;

	case SDL_MOUSEMOTION:
		SDL_GetMouseState(&x, &y);
		ResumeGameBtn->onHover(x, y);
		saveGameBtn->onHover(x, y);
		backBtn->onHover(x, y);
		quitGameBtn->onHover(x, y);
		break;
	default:
		break;
	}

}
