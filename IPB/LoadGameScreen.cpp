#include "pch.h"
#include <stdio.h>
#include "LoadGameScreen.h"
#include "LTexture.h"
#include "constants.h"
#include "Button.h"
#include "Game.h"

using namespace std;

LoadGameScreen::LoadGameScreen(SDL_Renderer* renderer, LTexture* imagesSpriteSheet) : renderer(renderer)
{
	int x = (constants::WINDOW_WIDTH - constants::BUTTON_WIDTH) / 2;
	selectSaved1Btn = new Button(imagesSpriteSheet, "Saved Game 1", x, 200);
	selectSaved2Btn = new Button(imagesSpriteSheet, "Saved Game 2", x, 200 + 65);
	selectSaved3Btn = new Button(imagesSpriteSheet, "Saved Game 3", x, 200 + 65 * 2);
	backBtn = new Button(imagesSpriteSheet, "Back to Menu", x, 200 + 65 * 3);

	string title = "Load Saved Game";
	ScreenTitle = new Word(title, imagesSpriteSheet, 10, 300); 
	ScreenTitle->setXCentered();
}

LoadGameScreen::~LoadGameScreen()
{
}
void LoadGameScreen::render()
{
	ScreenTitle->render(renderer);
	double y = ScreenTitle->getY();
	if (ScreenTitle->getY() > 100) // handle animation; move the title to y=100
		y = ScreenTitle->getY() * 0.9;
	else
	{
		selectSaved1Btn->render(renderer);
		selectSaved2Btn->render(renderer);
		selectSaved3Btn->render(renderer);
		backBtn->render(renderer);
	}

	ScreenTitle->setPosition(ScreenTitle->getX(), static_cast<int>(y));
}


void LoadGameScreen::handleEvents(SDL_Event& event)
{
	int x = 0; int y = 0;
	bool is1Clicked;
	bool is2Clicked;
	bool is3Clicked;
	bool isBackClicked;

	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		SDL_GetMouseState(&x, &y);
		selectSaved1Btn->onClickDown(x, y);
		selectSaved2Btn->onClickDown(x, y);
		selectSaved3Btn->onClickDown(x, y);
		backBtn->onClickDown(x, y);

		break;
	case SDL_MOUSEBUTTONUP:

		SDL_GetMouseState(&x, &y);
		is1Clicked = selectSaved1Btn->onClickUp(x, y);
		is2Clicked = selectSaved2Btn->onClickUp(x, y);
		is3Clicked = selectSaved3Btn->onClickUp(x, y);
		isBackClicked = backBtn->onClickUp(x, y);
		
		if (isBackClicked)
			Game::setCurrentScreen(constants::MAIN_MENU_SCREEN);
		else if (is1Clicked)
			Game::setCurrentScreen(constants::SAVE_GAME_SCREEN, "SavedGame1.txt");
		else if (is2Clicked)
			Game::setCurrentScreen(constants::SAVE_GAME_SCREEN, "SavedGame2.txt");
		else if (is3Clicked)
			Game::setCurrentScreen(constants::SAVE_GAME_SCREEN, "SavedGame3.txt");
		break;
	case SDL_MOUSEMOTION:
		SDL_GetMouseState(&x, &y);
		selectSaved1Btn->onHover(x, y);
		selectSaved2Btn->onHover(x, y);
		selectSaved3Btn->onHover(x, y);
		backBtn->onHover(x, y);
		break;
	default:
		break;
	}
}