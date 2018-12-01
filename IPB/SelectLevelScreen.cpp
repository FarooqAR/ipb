#include "pch.h"
#include <stdio.h>
#include "SelectLevelScreen.h"
#include "LTexture.h"
#include "constants.h"
#include "Button.h"
#include "Game.h"


SelectLevelScreen::SelectLevelScreen(SDL_Renderer* renderer, LTexture* imagesSpriteSheet) : renderer(renderer)
{
	
	int x = (constants::WINDOW_WIDTH - constants::BUTTON_WIDTH) / 2;

	lvl1 = new Button(imagesSpriteSheet, "Level 1", x, 200);
	lvl2 = new Button(imagesSpriteSheet, "Level 2", x, 200 + 80);
	lvl3 = new Button(imagesSpriteSheet, "Level 3", x, 200 + 80*2);
	lvl4 = new Button(imagesSpriteSheet, "Level 4", x, 200 + 80*3);
	BackBtn = new Button(imagesSpriteSheet, "Back", x, 250 + 80 * 4);

	string title = "Select Level";
	ScreenTitle = new Word(title, imagesSpriteSheet, 0, 300, 1); // 300 here is the starting y coord
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

