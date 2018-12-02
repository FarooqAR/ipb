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
	gameTitle->SetXCentered();
	Game::GetInstance()->PlayMusic(constants::MUSIC_THEME);
}
MainMenuScreen::~MainMenuScreen()
{

}
void MainMenuScreen::Render()
{
	gameTitle->Render(renderer);
	double y = gameTitle->GetY();
	if (gameTitle->GetY() > 100) // handle animation; move the title to y=100
		y = gameTitle->GetY() * 0.9;
	else
	{
		startGameBtn->Render(renderer);
		loadGameBtn->Render(renderer);
		selectLevelBtn->Render(renderer);
		quitGameBtn->Render(renderer);
	}

	gameTitle->SetPosition(gameTitle->GetX(), (int)y);
}



void MainMenuScreen::HandleEvents(SDL_Event& event)
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
		startGameBtn->OnClickDown(x, y);
		loadGameBtn->OnClickDown(x, y);
		selectLevelBtn->OnClickDown(x, y);
		quitGameBtn->OnClickDown(x, y);
		break;

	case SDL_MOUSEBUTTONUP:

		SDL_GetMouseState(&x, &y);
		isStartGameBtnClicked = startGameBtn->OnClickUp(x, y);
		isSelectLevelBtnClicked = selectLevelBtn->OnClickUp(x, y);
		isLoadGameBtnClicked = loadGameBtn->OnClickUp(x, y);
		isQuitGameBtnClicked = quitGameBtn->OnClickUp(x, y);
		if (isStartGameBtnClicked)
			Game::SetCurrentScreen(constants::BATTLE_SCREEN);
		else if (isLoadGameBtnClicked)
			Game::SetCurrentScreen(constants::LOAD_GAME_SCREEN);
		else if (isQuitGameBtnClicked)
		{
			delete Game::GetInstance();
			exit(0);
		}
		
		else if (isSelectLevelBtnClicked)
			Game::SetCurrentScreen(constants::SELECT_LEVEL_SCREEN);
		break;

	case SDL_MOUSEMOTION:
		SDL_GetMouseState(&x, &y);
		startGameBtn->OnHover(x, y);
		loadGameBtn->OnHover(x, y);
		selectLevelBtn->OnHover(x, y);
		quitGameBtn->OnHover(x, y);
		break;
	default:
		break;
	}
}
