#include "pch.h"
#include <stdio.h>
#include "MainMenuScreen.h"
#include "LTexture.h"
#include "constants.h"
#include "Button.h"
#include "Game.h"

MainMenuScreen::MainMenuScreen(SDL_Renderer* renderer, LTexture* imagesSpriteSheet) 
	: renderer(renderer)
{
	this->imagesSpriteSheet = imagesSpriteSheet;
	int x = (constants::WINDOW_WIDTH - constants::BUTTON_WIDTH) / 2;
	startGameBtn = new Button(imagesSpriteSheet, "Start Game", x, 200);
	loadGameBtn = new Button(imagesSpriteSheet, "Load Game", x, 200 + 65);
	selectLevelBtn = new Button(imagesSpriteSheet, "Select Level", x, 200 + 65 * 2);
	quitGameBtn = new Button(imagesSpriteSheet, "Quit Game", x, 200 + 65 * 3);

	string title = "Interplanetory Battlefield";
	gameTitle = new Word(title, imagesSpriteSheet, 0, 300, 1); // 300 here is the starting y coord
	gameTitle->setXCentered();
	Game::getInstance()->PlayMusic(constants::MUSIC_THEME);
}
MainMenuScreen::~MainMenuScreen()
{
	
}
void MainMenuScreen::render()
{
	gameTitle->render(renderer);
	double y = gameTitle->getY();
	if (gameTitle->getY() > 100) // handle animation; move the title to y=100
		y = gameTitle->getY() * 0.9;
	else
	{
		startGameBtn->render(renderer);
		loadGameBtn->render(renderer);
		selectLevelBtn->render(renderer);
		quitGameBtn->render(renderer);
	}

	gameTitle->setPosition(gameTitle->getX(), y);
}



void MainMenuScreen::handleEvents(SDL_Event& event)
{
	int x = 0; int y = 0;
	bool isStartGameBtnClicked;
	bool isQuitGameBtnClicked;
	bool isSelectLevelBtnClicked;

	bool isLoadGameBtnClicked;
	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		SDL_GetMouseState(&x, &y);
		startGameBtn->onClickDown(x, y);
		loadGameBtn->onClickDown(x, y);
		selectLevelBtn->onClickDown(x, y);
		quitGameBtn->onClickDown(x, y);
		break;
			
	case SDL_MOUSEBUTTONUP:

		SDL_GetMouseState(&x, &y);
		isStartGameBtnClicked = startGameBtn->onClickUp(x, y);
		isSelectLevelBtnClicked = selectLevelBtn->onClickUp(x, y);
		isLoadGameBtnClicked = loadGameBtn->onClickUp(x, y);
		isQuitGameBtnClicked = quitGameBtn->onClickUp(x, y);
		if (isStartGameBtnClicked)
			Game::setCurrentScreen(constants::BATTLE_SCREEN);
		else if (isLoadGameBtnClicked)
			Game::setCurrentScreen(constants::LOAD_GAME_SCREEN);
		else if (isQuitGameBtnClicked)
			exit(0);
		else if (isSelectLevelBtnClicked)
			Game::setCurrentScreen(constants::SELECT_LEVEL_SCREEN);
		break;

	case SDL_MOUSEMOTION:
		SDL_GetMouseState(&x, &y);
		startGameBtn->onHover(x, y);
		loadGameBtn->onHover(x, y);
		selectLevelBtn->onHover(x, y);
		quitGameBtn->onHover(x, y);
		break;
	default:
		break;
	}
}
