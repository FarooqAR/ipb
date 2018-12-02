#include "pch.h"
#include <iostream>
#include "Game.h"
#include "BattleScreen.h"
#include "MainMenuScreen.h"
#include "GameOverScreen.h"
#include "SelectLevelScreen.h"
#include "LoadGameScreen.h"
#include "LTexture.h"
#include <fstream>
#include <string>
#include "PauseScreen.h"
#include "ControlsIntroScreen.h"
#include <SDL.h>
#include <SDL_mixer.h>

using namespace std;

Game* Game::instance = nullptr;
GameScreen* Game::currentScreen = nullptr;
SDL_Renderer* Game::renderer = nullptr;
UnitFactory* Game::unitFactory = nullptr;
LTexture* Game::imagesSpriteSheet = nullptr;
bool Game::isFirstTimer = true;


Game::Game()
{
}

Game::~Game()
{
	clean();
}
Game * Game::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Game();
		instance->backgroundRect = { 0, 0, 1024, 786 };
	}
	return instance;
}

void Game::setCurrentScreen(int screen, const char* savedFilename)
{
	Game::getInstance()->StopMusic();
	if (screen == constants::MAIN_MENU_SCREEN)
	{
		currentScreen = new MainMenuScreen(renderer, imagesSpriteSheet);
	}
	else if (screen == constants::BATTLE_SCREEN)
	{
		if (isFirstTimer)
			currentScreen = new ControlsIntroScreen(renderer, imagesSpriteSheet);
		else
			currentScreen = new BattleScreen(renderer, unitFactory, imagesSpriteSheet);
		isFirstTimer = false;
	}
	else if (screen == constants::GAME_OVER_SCREEN)
	{
		currentScreen = new GameOverScreen(renderer, imagesSpriteSheet);
	}
	else if (screen == constants::SELECT_LEVEL_SCREEN)
	{
		currentScreen = new SelectLevelScreen(renderer, imagesSpriteSheet);
	}
	else if (screen == constants::LOAD_GAME_SCREEN)
	{
		currentScreen = new LoadGameScreen(renderer, imagesSpriteSheet);
	}
	/*else if (screen == constants::SAVE_GAME_SCREEN)
	{
		currentScreen = new BattleScreen(renderer, , unitFactory);
	}*/
	else if (screen == constants::PAUSE_SCREEN)
	{
		currentScreen = new PauseScreen(renderer, imagesSpriteSheet);
	}
	else if (screen == constants::LOAD_GAME_SCREEN)
	{
		currentScreen = new LoadGameScreen(renderer, imagesSpriteSheet);
	}
	else if (screen == constants::SAVE_GAME_SCREEN)
	{

		currentScreen = new BattleScreen(renderer, unitFactory, imagesSpriteSheet, savedFilename);

	}
	else if (screen == constants::PAUSE_SCREEN)
	{
		currentScreen = new PauseScreen(renderer, imagesSpriteSheet);
	}
}


void Game::init(const char * title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialized" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 100, 200, 150, 255);
			std::cout << "Renderer created!" << std::endl;
		}
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}
	unitFactory = UnitFactory::getInstance(renderer);
	imagesSpriteSheet = new LTexture;
	imagesSpriteSheet->loadFromFile("assets/images.png", renderer);
	themeChunk = Mix_LoadWAV("assets/sounds/theme.wav");
	explosionChunk = Mix_LoadWAV("assets/sounds/explosion.wav");
	btnClickChunk = Mix_LoadWAV("assets/sounds/button_press.wav");
	btnHoverChunk = Mix_LoadWAV("assets/sounds/button_hover.wav");
	bulletChunk = Mix_LoadWAV("assets/sounds/bullet.wav");
	setCurrentScreen(constants::MAIN_MENU_SCREEN);
}

void Game::PlayMusic(int MUSIC_TYPE)
{
	switch (MUSIC_TYPE)
	{
	case constants::MUSIC_BTN_CLICK:
		Mix_PlayChannel(-1, btnClickChunk, 0);
		break;
	case constants::MUSIC_BTN_HOVER:
		Mix_PlayChannel(-1, btnHoverChunk, 0);
		break;
	case constants::MUSIC_BULLET:
		Mix_PlayChannel(-1, bulletChunk, 0);
		break;
	case constants::MUSIC_EXPLOSION:
		Mix_PlayChannel(-1, explosionChunk, 0);
		break;
	case constants::MUSIC_THEME:
		Mix_PlayChannel(-1, themeChunk, 0);
		break;
	default:
		break;
	}
	
}
void Game::StopMusic(int channel)
{
	Mix_HaltChannel(channel);
}
void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
	currentScreen->handleEvents(event);
}

void Game::update()
{
	// update stuff
}

void Game::render()
{
	SDL_RenderClear(renderer);
	imagesSpriteSheet->renderTexture(0, 0, renderer, &backgroundRect);
	currentScreen->render();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	Mix_FreeChunk(btnClickChunk);
	Mix_FreeChunk(btnHoverChunk);
	Mix_FreeChunk(bulletChunk);
	Mix_FreeChunk(explosionChunk);
	Mix_FreeChunk(themeChunk);
	cout << SDL_GetError() << endl;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	delete currentScreen;
	std::cout << "Game clean" << std::endl;
}

bool Game::running()
{
	return isRunning;
}
