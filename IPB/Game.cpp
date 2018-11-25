#include "pch.h"
#include <iostream>
#include "Game.h"
#include "BattleScreen.h"
#include "MainMenuScreen.h"
#include "GameOverScreen.h"
#include "SelectLevelScreen.h"
#include "LTexture.h"
using namespace std;

Game* Game::instance = nullptr;
GameScreen* Game::currentScreen = nullptr;
SDL_Renderer* Game::renderer = nullptr;

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
		instance = new Game();
	return instance;
}
void Game::setCurrentScreen(int screen)
{
	delete currentScreen;
	if (screen == constants::MAIN_MENU_SCREEN)
	{
		currentScreen = new MainMenuScreen(renderer);
	}
	else if (screen == constants::BATTLE_SCREEN)
	{
		currentScreen = new BattleScreen(renderer);
	}
	else if (screen == constants::GAME_OVER_SCREEN)
	{
		currentScreen = new GameOverScreen(renderer);
	}
	else if (screen == constants::SELECT_LEVEL_SCREEN)
	{
		currentScreen = new SelectLevelScreen(renderer);
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
	currentScreen = new MainMenuScreen(renderer);
	backgroundTexture = new LTexture;
	backgroundTexture->loadFromFile("assets/space.jpg", renderer);
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
	backgroundTexture->renderTexture(0, 0, renderer);
	// render stuff
	currentScreen->render();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	cout << SDL_GetError() << endl;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	delete currentScreen;
	std::cout << "Game clean" << std::endl;
}

bool Game::running()
{
	return isRunning;
}
