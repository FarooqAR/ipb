#include "pch.h"
#include <stdio.h>
#include "LoadGameScreen.h"
#include "LTexture.h"
#include "constants.h"
#include "Button.h"
#include "Game.h"

using namespace std;

LoadGameScreen::LoadGameScreen(SDL_Renderer* renderer) : renderer(renderer)
{
	alphabetsSpriteSheet = new LTexture;
	buttonSpriteSheet = new LTexture;

	alphabetsSpriteSheet->loadFromFile("assets/spries.png", renderer, 1, 0, 0, 0);
	buttonSpriteSheet->loadFromFile("assets/button_sprite.png", renderer);

	int x = (constants::WINDOW_WIDTH - buttonSpriteSheet->getWidth()) / 2;
	selectSaved1Btn = new Button(buttonSpriteSheet, alphabetsSpriteSheet, "11-26 00:35:14", x, 200+70);
	selectSaved2Btn = new Button(buttonSpriteSheet, alphabetsSpriteSheet, "Saved Game 2", x, 200 + 65+70);
	selectSaved3Btn = new Button(buttonSpriteSheet, alphabetsSpriteSheet, "Saved Game 3", x, 200 + 65 * 2+70);
	backBtn = new Button(buttonSpriteSheet, alphabetsSpriteSheet, "Back to Menu", x, 200 + 65 * 3+70);

	string title = "Load Saved Game";
	string subtitle = "Choose the date";
	ScreenTitle = new Word(title, alphabetsSpriteSheet, 10, 300, 1.5); // 300 here is the starting y coord
	ScreenTitle->setXCentered();
	SubTitle = new Word(subtitle, alphabetsSpriteSheet, 350, 200, 0.7); // 300 here is the starting y coord
	//SubTitle->setXCentered();
}

LoadGameScreen::~LoadGameScreen()
{
}
void LoadGameScreen::render()
{
	ScreenTitle->render(renderer);
	SubTitle->render(renderer);
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

	ScreenTitle->setPosition(ScreenTitle->getX(), y);
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
			Game::setCurrentScreen(constants::SAVE_GAME_SCREEN);

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