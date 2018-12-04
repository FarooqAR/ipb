#include "pch.h"
#include "Node.h"
#include "BattleScreen.h"
#include "LTexture.h"
#include "Queue.h"
#include "Word.h"
#include "Attractor.h"
#include "EasterEgg.h"
#include "Unit.h"
#include "Player.h"
#include "Game.h"
#include "Enemy.h"
#include "Button.h"
#include "Word.h"
#include "orbs.h"
#include "UnitFactory.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <string>

using namespace std;

BattleScreen::BattleScreen(SDL_Renderer* renderer, UnitFactory* unitFactory, LTexture* imagesSpriteSheet)
	: renderer(renderer)
{
	isPaused = false;
	frames = 0;
	this->unitFactory = unitFactory;
	fadeScreenTexture = imagesSpriteSheet;
	explosionTexture = imagesSpriteSheet;
	healthBarTexture = imagesSpriteSheet;
	oxygenBarTexture = imagesSpriteSheet;
	fuelBarTexture = imagesSpriteSheet;
	bulletTexture = imagesSpriteSheet;
	wormHoleTexture = imagesSpriteSheet;
	oxygenEasterEggTexture = imagesSpriteSheet;
	healthEasterEggTexture = imagesSpriteSheet;
	fuelEasterEggTexture = imagesSpriteSheet;
	weaponEasterEggTexture = imagesSpriteSheet;
	AsteroidTexture = imagesSpriteSheet;

	asteroidClip = {
		constants::ASTEROID_SPRITE_START_POSITION.x,
		constants::ASTEROID_SPRITE_START_POSITION.y,
		constants::ASTEROID_WIDTH,
		constants::ASTEROID_HEIGHT
	};
	healthEasterEggClip = {
		constants::FOOD_SPRITE_START_POSITION.x,
		constants::FOOD_SPRITE_START_POSITION.y,
		constants::FOOD_WIDTH,
		constants::FOOD_HEIGHT
	};
	oxygenEasterEggClip = {
		constants::ASTRONAUT_SPRITE_START_POSITION.x,
		constants::ASTRONAUT_SPRITE_START_POSITION.y,
		constants::ASTRONAUT_WIDTH,
		constants::ASTRONAUT_HEIGHT
	};
	fuelEasterEggClip = {
		constants::FUELTANK_SPRITE_START_POSITION.x,
		constants::FUELTANK_SPRITE_START_POSITION.y,
		constants::FUELTANK_WIDTH,
		constants::FUELTANK_HEIGHT
	};
	weaponEasterEggClip = {
		constants::LAUNCHER_SPRITE_START_POSITION.x,
		constants::LAUNCHER_SPRITE_START_POSITION.y,
		constants::LAUNCHER_WIDTH,
		constants::LAUNCHER_HEIGHT
	};
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

	//The end destination the player has to reach
	wormHole = new Unit(renderer, wormHoleTexture, 0, 0, 0);
	wormHole->SetPosition(100, 300);
	wormHole->SetClip(wormHoleClip);

	//creates player, enemy, planets 
	hero = new Player(renderer, imagesSpriteSheet, constants::WINDOW_WIDTH / 2, constants::WINDOW_HEIGHT - 100);
	enemy = new Enemy(renderer, imagesSpriteSheet, constants::WINDOW_WIDTH - 200, 30);
	int x = (constants::WINDOW_WIDTH - constants::BUTTON_WIDTH) / 2;
	resumeGameBtn = new Button(imagesSpriteSheet, "Resume", x, 200);
	saveGameBtn = new Button(imagesSpriteSheet, "Save Game", x, 200 + 65);
	backBtn = new Button(imagesSpriteSheet, "Back to Menu", x, 200 + 65 * 2);
	quitGameBtn = new Button(imagesSpriteSheet, "Quit", x, 200 + 65 * 3);

	pauseTitle = new Word("Game Paused", imagesSpriteSheet, 0, 300, 1); // 300 here is the starting y coord
	pauseTitle->SetXCentered();

	//generates movement orbs
	ball = new Orbs*[10];
	for (int x = 0; x < 10; x++)
	{
		ball[x] = new Orbs(renderer, constants::WINDOW_WIDTH / 2, constants::WINDOW_HEIGHT - 100, .09f / (x + 3));
	}

	for (int i = 0; i < 20; i++)
	{
		explosionSpriteClips[i] = { constants::EXPLOSION_SPRITE_START_POSITION.x + 96 * i, constants::EXPLOSION_SPRITE_START_POSITION.y, 96, 96 };
	}
	string title = "Weapon: " + hero->GetWeaponName();
	weaponTitle = new Word(title, imagesSpriteSheet, 20, constants::WINDOW_HEIGHT - 50, 0.27f);
	title = "Ammo: " + to_string(hero->GetAmmo());
	ammoCount = new Word(title, imagesSpriteSheet, 20, constants::WINDOW_HEIGHT - 25, 0.27f);
	enemyHealthBoundary = { 0, 0, 95, 10 };
	heroHealthBoundary = { constants::WINDOW_WIDTH - 130, constants::WINDOW_HEIGHT - 50, 105, 10 };
	heroOxygenBoundary = { constants::WINDOW_WIDTH - 130, constants::WINDOW_HEIGHT - 35, 105, 10 };
	heroFuelBoundary = { constants::WINDOW_WIDTH - 130, constants::WINDOW_HEIGHT - 20, 105, 10 };
}

BattleScreen::BattleScreen(SDL_Renderer* renderer, UnitFactory* unitFactory, LTexture* imagesSpriteSheet, const char* savedFileName)
	: BattleScreen(renderer, unitFactory, imagesSpriteSheet)
{
	//reading from file
	ifstream file(savedFileName);
	string line;
	bool readingPlanets = false;
	bool readingAsteroids = false;

	if (!file || !file.is_open())
		return;
	int i = 1;
	Point pos;
	//reads each line and acts accordingly 
	while (getline(file, line))
	{
		switch (i)
		{
		case 1:
			pos.x = stoi(line);
			break;
		case 2:
			pos.y = stoi(line);
			hero->SetPosition(pos.x, pos.y);
			break;
		case 3:
			hero->SetAngle(stod(line));
			break;
		case 4:
			hero->SetHealth(stof(line));
			break;
		case 5:
			hero->SetOxygen(float(stoi(line)));
			break;
		case 6:
			hero->SetFuel(float(stoi(line)));
			break;
		case 7:
			hero->GetWeapon()->SetWeaponType(stoi(line));
			weaponTitle->SetText("Weapon: " + hero->GetWeaponName());
			break;
		case 8:
			hero->SetAmmo(stoi(line));
			ammoCount->SetText("Ammo: " + to_string(hero->GetAmmo()));
			break;
		case 9:
			hero->SetShipCurrentClipIndex(stoi(line));
			break;
		case 10:
			pos.x = stoi(line);
			break;
		case 11:
			pos.y = stoi(line);
			enemy->SetPosition(pos.x, pos.y);
			break;
		case 12:
			enemy->SetAngle(stod(line));
			break;
		case 13:
			enemy->SetHealth(stof(line));
			break;
		default:
			break;
		}
		if (line == "planets")
		{
			readingPlanets = true;
			continue;
		}
		else if (line == "asteroids")
		{
			readingPlanets = false;
			readingAsteroids = true;
			continue;
		}
		if (readingPlanets)
		{
			string tokens = "";
			int x;
			int y;
			float scale;
			int j = 0;
			int k = 0;
			int planetType = 0;
			while (j != line.length())
			{
				if (line[j] == ' ' || j == line.length() - 1)
				{
					if (k == 0) x = stoi(tokens);
					else if (k == 1) y = stoi(tokens);
					else if (k == 2) planetType = stoi(tokens);
					else scale = stof(tokens + line[j]);
					k++;
					tokens = "";
				}
				else
				{
					tokens += line[j];
				}
				j++;
			}
			planets.Enqueue(unitFactory->CreatePlanet(imagesSpriteSheet, planetType, x, y, scale));
		}
		i++;

	}
	file.close();
}


BattleScreen::~BattleScreen()
{

}

void BattleScreen::Render()
{
	planets.Render();
	weaponTitle->Render(renderer);
	ammoCount->Render(renderer);
	enemyHealthBoundary.x = enemy->GetPosition().x;
	enemyHealthBoundary.y = enemy->GetPosition().y - 10;
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 1);
	if (enemy->GetAlive())
		SDL_RenderDrawRect(renderer, &enemyHealthBoundary);
	//renders boundaries for status bars
	SDL_RenderDrawRect(renderer, &heroHealthBoundary);
	SDL_SetRenderDrawColor(renderer, 88, 180, 180, 1);
	SDL_RenderDrawRect(renderer, &heroOxygenBoundary);
	SDL_SetRenderDrawColor(renderer, 228, 123, 36, 1);
	SDL_RenderDrawRect(renderer, &heroFuelBoundary);

	//renders  status bars
	RenderStatusBars();
	//renders an easter egg at random
	RenderRandomEasterEggs();

	// renders wormhole
	if (!enemy->GetAlive() && hero->GetAlive())
		RenderWormHole();

	// renders hero
	RenderPlayer();

	// renders enemy
	RenderEnemy();

	//kills both enemy and hero if they collide
	if (enemy->GetAlive() && hero->CheckCollision(enemy))
	{
		hero->SetHealth(0);
		enemy->SetHealth(0);
	}

	//does damage if hero gets hit by bullet
	if (enemy->GetAlive() && playerBulletQueue.CheckCollision(enemy, true))
	{
		enemy->SetHealth(enemy->GetHealth() - hero->GetWeapon()->GetDamage());
		playerBulletQueue.Clean();
	}
	//does damage if enemy gets hit by bullet
	if (enemyBulletQueue.CheckCollision(hero, true))
	{
		hero->SetHealth(hero->GetHealth() - 5);
		enemyBulletQueue.Clean();
	}

	if (!isPaused)
	{
		playerBulletQueue.Move();
		enemyBulletQueue.Move();
		asteroidQueue.Move();
		easterEggQueue.Move();

	}
	playerBulletQueue.Render();
	enemyBulletQueue.Render();
	asteroidQueue.Render();
	easterEggQueue.Render();
	
	//decrements the fuel bar when thrusting, and the oxygen bar with time
	if (int(hero->GetFuel()) < 100 && hero->GetIsThrusting() == 0)
	{
		hero->SetFuel(float(int(hero->GetFuel()) + 1));
	}

	if (frames % 100 == 0)
	{
		hero->SetOxygen(hero->GetOxygen() - 1);
	}
	
	//renders an asteroid 
	if (frames % 150 == 0)
	{
		Asteroid* spawnAsteroid = new Asteroid(renderer, AsteroidTexture, float(0.3));
		spawnAsteroid->SetClip(asteroidClip);
		asteroidQueue.Enqueue(spawnAsteroid);
	}

	//checks if the player has has collected the easteregg
	bool collected = easterEggQueue.CheckCollision(hero, true);

	if (collected && !isPaused)
	{
		//updates the status of the player and screen if easteregg collected
		easterEggQueue.Collected(hero);
		string title = "Weapon: " + string(hero->GetWeapon()->GetWeaponName());
		weaponTitle->SetText(title);
		title = "Ammo: " + to_string(hero->GetAmmo());
		ammoCount->SetText(title);
	}


	//checks if asteroid made contact with either the hero or enemy
	bool asteroidCollision = asteroidQueue.CheckCollision(hero, true);
	bool asteroidCollisionEnemy = asteroidQueue.CheckCollision(enemy, true);
	//checks each object of one queue (asteroid) with each time of another (bullets and planets) to see if collision occured 
	asteroidQueue.CheckCollision(&playerBulletQueue, explosionTexture, explosionSpriteClips, true);
	asteroidQueue.CheckCollision(&enemyBulletQueue, explosionTexture, explosionSpriteClips, true);
	asteroidQueue.CheckCollision(&planets, explosionTexture, explosionSpriteClips);

	if (asteroidCollision)
	{
		hero->SetHealth(hero->GetHealth() - 10);
		hero->Explosion(explosionTexture, explosionSpriteClips, hero);

	}

	if (asteroidCollisionEnemy)
	{
		enemy->Explosion(explosionTexture, explosionSpriteClips, enemy);
	}
	
	planets.Clean();
	asteroidQueue.Clean();
	easterEggQueue.Clean();

	//while both enemy and hero are alive, the enemy shoots bullets
	if (enemy->GetAlive() && hero->GetAlive() && !isPaused)
	{
		if (frames % 50 == 0)
		{
			ShootEnemyBullet();
		}

	}
	   
	//checks for paused game
	if (isPaused)
	{
		RenderFadeScreen();
	}
	hero->SetDelay(hero->GetDelay() - 1);
	frames++;
}

void BattleScreen::RenderWormHole()
{
	wormHole->SetAngle(wormHole->GetAngle() - 0.2);
	if (!intoWormHole)
	{
		wormHole->SetScale(wormHole->GetScale() + 0.1f);
	}
	else
	{
		hero->SetScale(hero->GetScale() - 0.1f);
	}
	if (wormHole->CheckCollision(hero, true))
	{
		intoWormHole = true;
	}
	wormHole->Render();
}

void BattleScreen::RenderStatusBars()
{
	int i = 0;
	//fill the bars
	while (i < hero->GetHealth())
	{
		healthBarTexture->RenderTexture(constants::WINDOW_WIDTH - 130 + i, constants::WINDOW_HEIGHT - 50, renderer, &healthSpriteClip);
		i += 1;
	}
	i = 0;
	while (i < hero->GetOxygen())
	{
		oxygenBarTexture->RenderTexture(constants::WINDOW_WIDTH - 130 + i, constants::WINDOW_HEIGHT - 35, renderer, &oxygenSpriteClip);
		i += 1;
	}
	i = 0;
	while (i < hero->GetFuel())
	{
		fuelBarTexture->RenderTexture(constants::WINDOW_WIDTH - 130 + i, constants::WINDOW_HEIGHT - 20, renderer, &fuelSpriteClip);
		i += 1;
	}
	i = 0;
	while (i < enemy->GetHealth())
	{
		healthBarTexture->RenderTexture((int)(enemy->GetPosition().x + i * 0.9), enemy->GetPosition().y - 10, renderer, &healthSpriteClip);
		i += 1;
	}
}

void BattleScreen::RenderRandomEasterEggs()
{
	if (frames % 400 == 0 && !isPaused)
	{
		int type = rand() % 4;
		LTexture* texture = healthEasterEggTexture;
		SDL_Rect clip;

		switch (type)
		{
		case 0:
		{
			texture = healthEasterEggTexture;
			clip = healthEasterEggClip;
			break;
		}
		case 1:
		{
			texture = fuelEasterEggTexture;
			clip = fuelEasterEggClip;
			break;
		}
		case 2:
		{
			texture = oxygenEasterEggTexture;
			clip = oxygenEasterEggClip;
			break;
		}
		case 3:
		{
			texture = weaponEasterEggTexture;
			clip = weaponEasterEggClip;
			break;
		}
		}

		EasterEgg* bonus = unitFactory->CreateEasterEgg(texture, type);

		do
		{
			bonus->SetClip(clip);
			bonus->SetPosition((rand() % 501 + 100), (rand() % 826 + 100));
		} while (planets.CheckCollision(bonus) && easterEggQueue.CheckCollision(bonus));
		easterEggQueue.Enqueue(bonus);
	}
}

void BattleScreen::RenderPlayer()
{
	//checks if hero is in contact with planets
	bool isColliding = planets.CheckCollision(hero) && !isPaused;
	// toggle ship color when it collides
	if (isColliding)
	{
		hero->SetHealth(hero->GetHealth() - 0.1f);
		if (frames % 20 == 0)
		{
			if (hero->GetIsThrusting())
			{
				if (hero->GetCurrentClipIndex() == 9)
					hero->SetShipCurrentClipIndex(10);
				else
					hero->SetShipCurrentClipIndex(9);
			}
			else
			{

				if (hero->GetCurrentClipIndex() == 1)
					hero->SetShipCurrentClipIndex(2);
				else
					hero->SetShipCurrentClipIndex(1);
			}
		}
	}
	else if (!isPaused)
	{
		if (hero->GetIsThrusting())
		{
			if (frames % 3 == 0)
				hero->ChangeShipCurrentClipIndex();
		}
		else
		{
			hero->SetShipCurrentClipIndex(0);
		}
	}
	if (hero->GetAlive())
	{
		if (hero->GetScale() > 0.1)
		{
			for (int x = 0; x < 10; x++)
			{
				ball[x]->Render();
			}
			hero->Render();
		}
		else
			Game::GetInstance()->SetCurrentScreen(constants::SELECT_LEVEL_SCREEN);


	}
	//if hero != alive, there is an explosion
	else if (heroExplosionSpriteIndex < 20)
	{
		if (heroExplosionSpriteIndex == 0)
			Game::GetInstance()->PlayMusic(constants::MUSIC_EXPLOSION);

		explosionTexture->RenderTexture(
			hero->GetPosition().x + hero->GetWidth() / 2 - 96 / 2,
			hero->GetPosition().y + hero->GetHeight() / 2 - 96 / 2,
			renderer,
			&explosionSpriteClips[heroExplosionSpriteIndex]
		);
		if (frames % 4 == 0)
			heroExplosionSpriteIndex++;
		if (heroExplosionSpriteIndex == 19)
			Game::GetInstance()->SetCurrentScreen(constants::GAME_OVER_SCREEN);
	}
}

void BattleScreen::RenderEnemy()
{
	if (enemy->GetAlive())
	{
		enemy->Render();
	}
	//explosion if enemy is dead
	else if (enemExplosionSpriteIndex < 20)
	{
		if (enemExplosionSpriteIndex == 0)
			Game::GetInstance()->PlayMusic(constants::MUSIC_EXPLOSION);

		explosionTexture->RenderTexture(
			enemy->GetPosition().x + enemy->GetWidth() / 2 - 100 / 2,
			enemy->GetPosition().y + enemy->GetHeight() / 2 - 63 / 2,
			renderer,
			&explosionSpriteClips[enemExplosionSpriteIndex]
		);
		if (frames % 4 == 0)
		{
			enemExplosionSpriteIndex++;
		}
	}

}

void BattleScreen::RenderFadeScreen()
{
	fadeScreenTexture->RenderTexture(25, 50, renderer, &pauseScreenSpriteClip);

	pauseTitle->Render(renderer);
	double y = pauseTitle->GetY();
	if (pauseTitle->GetY() > 100) // handle animation; move the title to y=100
		y = pauseTitle->GetY() * 0.9;
	else
	{
		resumeGameBtn->Render(renderer);
		saveGameBtn->Render(renderer);
		backBtn->Render(renderer);
		quitGameBtn->Render(renderer);
	}

	pauseTitle->SetPosition(pauseTitle->GetX(), (int)y);
}

void BattleScreen::ShootEnemyBullet()
{
	Bullet *bullet = enemy->GetWeapon()->Fire(
		renderer,
		bulletTexture,
		enemy->GetPosition().x + enemy->GetWidth() / 2,
		enemy->GetPosition().y + enemy->GetHeight() / 2,
		atan2(
			hero->GetPosition().x + hero->GetWidth() / 2 - enemy->GetPosition().x - enemy->GetWidth() / 2,
			enemy->GetPosition().y + enemy->GetHeight() / 2 - hero->GetPosition().y - hero->GetHeight() / 2
		) * 180 / constants::PI
	);
	enemyBulletQueue.Enqueue(bullet);
}


bool BattleScreen::IsEmpty(string filename)
{
	ifstream file;
	int length;
	file.open(filename);
	file.seekg(0, ios::end); // put the "cursor" at the end of the file
	length = (int)file.tellg(); // find the position of the cursor

	if (length == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void BattleScreen::WriteFile(string filename)
{
	ofstream myfile;
	Node* planetsCursor;
	myfile.open(filename);
	myfile <<
		hero->GetPosition().x << endl <<
		hero->GetPosition().y << endl <<
		hero->GetAngle() << endl <<
		hero->GetHealth() << endl <<
		hero->GetOxygen() << endl <<
		hero->GetFuel() << endl <<
		hero->GetWeapon()->GetWeaponType() << endl <<
		hero->GetAmmo() << endl <<
		hero->GetCurrentClipIndex() << endl <<
		enemy->GetPosition().x << endl <<
		enemy->GetPosition().y << endl <<
		enemy->GetAngle() << endl <<
		enemy->GetHealth() << endl
		<< "planets" << endl;
	planetsCursor = planets.Top();
	while (planetsCursor != nullptr)
	{
		myfile <<
			planetsCursor->unit->GetPosition().x << " " <<
			planetsCursor->unit->GetPosition().y << " " <<
			((Attractor*)planetsCursor->unit)->GetPlanetType() << " " <<
			planetsCursor->unit->GetScale() << endl;
		planetsCursor = planetsCursor->next;
	}
	myfile.close();
}



void BattleScreen::HandleEvents(SDL_Event& event)
{
	int x = 0; int y = 0;

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);


	//handles running game
	if (!isPaused)
	{
		//moving right
		if (currentKeyStates[SDL_SCANCODE_RIGHT])
		{
			hero->Move(RIGHT);
		}

		//moving left
		if (currentKeyStates[SDL_SCANCODE_LEFT])
		{
			hero->Move(LEFT);
		}

		//moving up
		if (currentKeyStates[SDL_SCANCODE_UP] && hero->GetAlive())
		{
			hero->Move(UP);
			hero->SetIsThrusting(true); //shows thruster
			hero->SetFuel(float(hero->GetFuel() - 0.4));
		}
		else if (hero->GetAlive())
		{
			hero->SetIsThrusting(false);
			planets.Pull(hero);
			if (!intoWormHole)
				hero->Move();
		}

		//iterates through orbs
		for (int y = 0; y < 10; y++)
		{
			// sets all to current hero position
			ball[y]->SetPosition(hero);
			for (int z = y; z < 6 * y; z++)
			{
				//pulls orbs accordingly 
				planets.Pull(ball[y]);
				ball[y]->Move();
			}
		}
	}
	//space for shooting
	if (currentKeyStates[SDL_SCANCODE_SPACE] && isPaused == false)
	{
		if (hero->GetDelay() == 0 && hero->GetAmmo() > 0 && !intoWormHole)
		{
			//updates screen once the player shoots a bullet
			Bullet *bullet = hero->Shoot(renderer, bulletTexture);
			playerBulletQueue.Enqueue(bullet);
			hero->SetDelay(hero->GetWeapon()->GetDelay());
			hero->SetAmmo(hero->GetAmmo() - 1);
			string title = "Ammo: " + to_string(hero->GetAmmo());
			ammoCount->SetText(title);
		}
	}
	bool isResumeGameBtnClicked = false;
	bool isBackBtnClicked = false;
	bool isQuitGameBtnClicked = false;
	bool issaveGameBtnClicked = false;
	switch (event.type)
	{
	case SDL_KEYUP:
		if (event.key.keysym.sym == SDLK_ESCAPE)
			isPaused = !isPaused;
		break;
	case SDL_MOUSEBUTTONDOWN:
		SDL_GetMouseState(&x, &y);
		if (isPaused)
		{
			resumeGameBtn->OnClickDown(x, y);
			saveGameBtn->OnClickDown(x, y);
			backBtn->OnClickDown(x, y);
			quitGameBtn->OnClickDown(x, y);

		}

		break;
	case SDL_MOUSEBUTTONUP:

		SDL_GetMouseState(&x, &y);
		if (isPaused)
		{
			isResumeGameBtnClicked = resumeGameBtn->OnClickUp(x, y);
			issaveGameBtnClicked = saveGameBtn->OnClickUp(x, y);
			isBackBtnClicked = backBtn->OnClickUp(x, y);
			isQuitGameBtnClicked = quitGameBtn->OnClickUp(x, y);
		}
		if (isResumeGameBtnClicked)
			isPaused = false;
		else if (issaveGameBtnClicked)
		{
			if (IsEmpty("SavedGame1.txt") == true)
			{
				WriteFile("SavedGame1.txt");
			}
			else
			{
				if (IsEmpty("SavedGame2.txt") == true)
				{
					WriteFile("SavedGame2.txt");
				}
				else
				{
					if (IsEmpty("SavedGame3.txt") == true)
					{
						WriteFile("SavedGame3.txt");
					}
					else
					{
						WriteFile("SavedGame1.txt");
					}
				}
			}

			Game::GetInstance()->SetCurrentScreen(constants::MAIN_MENU_SCREEN);
		}
		else if (isBackBtnClicked)
			Game::GetInstance()->SetCurrentScreen(constants::MAIN_MENU_SCREEN);
		else if (isQuitGameBtnClicked)
		{
			exit(0);
		}
		break;

	case SDL_MOUSEMOTION:
		SDL_GetMouseState(&x, &y);
		if (isPaused)
		{
			resumeGameBtn->OnHover(x, y);
			saveGameBtn->OnHover(x, y);
			backBtn->OnHover(x, y);
			quitGameBtn->OnHover(x, y);
		}
		break;
	default:
		break;
	}

}
