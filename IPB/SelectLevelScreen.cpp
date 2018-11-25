#include "pch.h"
#include <stdio.h>
#include "SelectLevelScreen.h"
#include "LTexture.h"
#include "constants.h"
#include "Button.h"
#include "Game.h"


SelectLevelScreen::SelectLevelScreen(SDL_Renderer* renderer) : renderer(renderer)
{
	alphabetsSpriteSheet = new LTexture;
	buttonSpriteSheet = new LTexture;

	alphabetsSpriteSheet->loadFromFile("assets/spries.png", renderer, 1, 0, 0, 0);
	buttonSpriteSheet->loadFromFile("assets/button_sprite.png", renderer);
	int x = (constants::WINDOW_WIDTH - buttonSpriteSheet->getWidth()) / 2;

	lvl1 = new Button(buttonSpriteSheet, alphabetsSpriteSheet, "Level 1: Intro to Galaxy", x - 120, 200, 560, 52);
	lvl2 = new Button(buttonSpriteSheet, alphabetsSpriteSheet, "Level 2: Save Elon Musk", x - 120, 200 + 80, 560, 52);
	lvl3 = new Button(buttonSpriteSheet, alphabetsSpriteSheet, "Level 3: Into the Warzone", x - 120, 200 + 80*2, 560, 52);
	lvl4 = new Button(buttonSpriteSheet, alphabetsSpriteSheet, "Level 4: The fake Rambo", x - 120, 200 + 80*3, 560, 52);

	BackBtn = new Button(buttonSpriteSheet, alphabetsSpriteSheet, "Back", x - 120, 250 + 80 * 4, 150, 52);

	string title = "Select Level";
	ScreenTitle = new Word(title, alphabetsSpriteSheet, 0, 300, 1); // 300 here is the starting y coord
	ScreenTitle->setXCentered();
}

SelectLevelScreen::~SelectLevelScreen()
{
}

void SelectLevelScreen::render()
{
	ScreenTitle->render(renderer);
	double y = ScreenTitle->getY();
	if (ScreenTitle->getY() > 100) // handle animation; move the title to y=100
		y = ScreenTitle->getY() * 0.9;
	else
	{
		lvl1->render(renderer);
		lvl2->render(renderer);
		lvl3->render(renderer);
		lvl4->render(renderer);
		BackBtn->render(renderer);
	}

	ScreenTitle->setPosition(ScreenTitle->getX(), y);
}


void SelectLevelScreen::handleEvents(SDL_Event& event)
{
	int x = 0; int y = 0;
	bool isBackBtnClicked;
	bool isLvl1Clicked;

	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		SDL_GetMouseState(&x, &y);
		BackBtn->onClickDown(x, y);
		lvl1->onClickDown(x, y);
		break;

	case SDL_MOUSEBUTTONUP:

		SDL_GetMouseState(&x, &y);
		isBackBtnClicked = BackBtn->onClickUp(x, y);
		isLvl1Clicked = lvl1->onClickUp(x, y);
		if (isBackBtnClicked)
			Game::setCurrentScreen(constants::MAIN_MENU_SCREEN);
		if (isLvl1Clicked)
			Game::setCurrentScreen(constants::BATTLE_SCREEN);
		break;

	case SDL_MOUSEMOTION:
		SDL_GetMouseState(&x, &y);
		BackBtn->onHover(x, y);
		lvl1->onHover(x, y);

		break;
	default:
		break;
	}
}

