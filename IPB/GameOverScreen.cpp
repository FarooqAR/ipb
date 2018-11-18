#include "pch.h"
#include <stdio.h>
#include "GameOverScreen.h"
#include "LTexture.h"
#include "constants.h"
#include "Button.h"
#include "Game.h"

GameOverScreen::GameOverScreen(SDL_Renderer* renderer) : renderer(renderer)
{
	alphabetsSpriteSheet = new LTexture;
	buttonSpriteSheet = new LTexture;

	alphabetsSpriteSheet->loadFromFile("assets/spries.png", renderer, 1, 0, 0, 0);
	buttonSpriteSheet->loadFromFile("assets/button_sprite.png", renderer);
	int x = (constants::WINDOW_WIDTH - buttonSpriteSheet->getWidth()) / 2;
	mainMenuBtn = new Button(buttonSpriteSheet, alphabetsSpriteSheet, "Main Menu", x, 400);
	quitBtn = new Button(buttonSpriteSheet, alphabetsSpriteSheet, "Quit", x, 400 + 65);

	string title = "Game Over!";
	gameOverTitle = new Word(title, alphabetsSpriteSheet, 0, 300, 1); // 300 here is the starting y coord, it will animate to 100
	gameOverTitle->setXCentered(); // puts word at the center of the screen

}
GameOverScreen::~GameOverScreen()
{
	delete alphabetsSpriteSheet;
	delete buttonSpriteSheet;
	delete mainMenuBtn;
	delete quitBtn;
	delete gameOverTitle;
}
void GameOverScreen::render()
{
	gameOverTitle->render(renderer);
	mainMenuBtn->render(renderer);
	quitBtn->render(renderer);
}
void GameOverScreen::handleEvents(SDL_Event& event)
{
	int x = 0; int y = 0;
	bool isMainMenuBtnClicked;
	bool isQuitBtnClicked;
	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		SDL_GetMouseState(&x, &y);
		mainMenuBtn->onClickDown(x, y);
		quitBtn->onClickDown(x, y);

		break;
	case SDL_MOUSEBUTTONUP:

		SDL_GetMouseState(&x, &y);
		isQuitBtnClicked = quitBtn->onClickUp(x, y);
		isMainMenuBtnClicked = mainMenuBtn->onClickUp(x, y);
		if (isMainMenuBtnClicked)
			Game::setCurrentScreen(constants::MAIN_MENU_SCREEN);
		else if (isQuitBtnClicked)
			exit(0); // needs change; should signal Game.cpp which will exit properly

		break;
	case SDL_MOUSEMOTION:
		SDL_GetMouseState(&x, &y);
		mainMenuBtn->onHover(x, y);
		quitBtn->onHover(x, y);
		break;
	default:
		break;
	}
}