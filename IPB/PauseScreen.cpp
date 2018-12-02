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
	gameTitle->SetXCentered();
}

PauseScreen::~PauseScreen()
{
}
void PauseScreen::Render()
{
	gameTitle->Render(renderer);
	double y = gameTitle->GetY();
	if (gameTitle->GetY() > 100) // handle animation; move the title to y=100
		y = gameTitle->GetY() * 0.9;
	else
	{
		ResumeGameBtn->Render(renderer);
		saveGameBtn->Render(renderer);
		backBtn->Render(renderer);
		quitGameBtn->Render(renderer);
	}

	gameTitle->SetPosition(gameTitle->GetX(), (int)y);
}



void PauseScreen::HandleEvents(SDL_Event& event)
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
		ResumeGameBtn->OnClickDown(x, y);
		saveGameBtn->OnClickDown(x, y);
		backBtn->OnClickDown(x, y);
		quitGameBtn->OnClickDown(x, y);

		break;
	case SDL_MOUSEBUTTONUP:

		SDL_GetMouseState(&x, &y);
		isResumeGameBtnClicked = ResumeGameBtn->OnClickUp(x, y);
		issaveGameBtnClicked = saveGameBtn->OnClickUp(x, y);
		isBackBtnClicked = backBtn->OnClickUp(x, y);
		isQuitGameBtnClicked = quitGameBtn->OnClickUp(x, y);
		if (isResumeGameBtnClicked)
			Game::SetCurrentScreen(constants::BATTLE_SCREEN);
		else if (isBackBtnClicked)
			Game::SetCurrentScreen(constants::MAIN_MENU_SCREEN);
		else if (isQuitGameBtnClicked)
			exit(0);
		break;

	case SDL_MOUSEMOTION:
		SDL_GetMouseState(&x, &y);
		ResumeGameBtn->OnHover(x, y);
		saveGameBtn->OnHover(x, y);
		backBtn->OnHover(x, y);
		quitGameBtn->OnHover(x, y);
		break;
	default:
		break;
	}
}