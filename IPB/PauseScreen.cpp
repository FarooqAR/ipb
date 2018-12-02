#include "pch.h"
#include <stdio.h>
#include "PauseScreen.h"
#include "LTexture.h"
#include "constants.h"
#include "Button.h"
#include "Game.h"


PauseScreen::PauseScreen(SDL_Renderer* renderer, LTexture* imagesSpriteSheet) : renderer(renderer)
{
	int x = (constants::WINDOW_WIDTH - constants::BUTTON_WIDTH) / 2;
	ResumeGameBtn = new Button(imagesSpriteSheet, "Resume", x, 200);
	saveGameBtn = new Button(imagesSpriteSheet, "Save Game", x, 200 + 65);
	backBtn = new Button(imagesSpriteSheet, "Back to Menu", x, 200 + 65 * 2);
	quitGameBtn = new Button(imagesSpriteSheet, "Quit", x, 200 + 65 * 3);

	string title = "Game Paused";
	gameTitle = new Word(title, imagesSpriteSheet, 0, 300, 1); // 300 here is the starting y coord
	gameTitle->setXCentered();
}

PauseScreen::~PauseScreen()
{
}
void PauseScreen::render()
{
	gameTitle->render(renderer);
	double y = gameTitle->getY();
	if (gameTitle->getY() > 100) // handle animation; move the title to y=100
		y = gameTitle->getY() * 0.9;
	else
	{
		ResumeGameBtn->render(renderer);
		saveGameBtn->render(renderer);
		backBtn->render(renderer);
		quitGameBtn->render(renderer);
	}

	gameTitle->setPosition(gameTitle->getX(), static_cast<int>(y));
}



void PauseScreen::handleEvents(SDL_Event& event)
{
	int x = 0; int y = 0;
	bool isResumeGameBtnClicked;
	bool isBackBtnClicked;
	bool isQuitGameBtnClicked;
	bool issaveGameBtnClicked;
	switch (event.type)
	{
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
			Game::setCurrentScreen(constants::BATTLE_SCREEN);
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