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
	lvl2 = new Button(imagesSpriteSheet, "Level 2", x, 200 + 65);
	lvl3 = new Button(imagesSpriteSheet, "Level 3", x, 200 + 65 * 2);
	BackBtn = new Button(imagesSpriteSheet, "Back", x, 250 + 65 * 3);

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
		BackBtn->render(renderer);
	}

	ScreenTitle->setPosition(ScreenTitle->getX(), (int)y);
}


void SelectLevelScreen::handleEvents(SDL_Event& event)
{
	int x = 0; int y = 0;
	bool isBackBtnClicked;
	bool isLvl1Clicked;
	bool isLvl2Clicked;
	bool isLvl3Clicked;

	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		SDL_GetMouseState(&x, &y);
		BackBtn->onClickDown(x, y);
		lvl1->onClickDown(x, y);
		lvl2->onClickDown(x, y);
		lvl3->onClickDown(x, y);
		break;

	case SDL_MOUSEBUTTONUP:

		SDL_GetMouseState(&x, &y);
		isBackBtnClicked = BackBtn->onClickUp(x, y);
		isLvl1Clicked = lvl1->onClickUp(x, y);
		isLvl2Clicked = lvl2->onClickUp(x, y);
		isLvl3Clicked = lvl3->onClickUp(x, y);
		if (isBackBtnClicked)
			Game::setCurrentScreen(constants::MAIN_MENU_SCREEN);
		if (isLvl1Clicked)
			Game::setCurrentScreen(constants::BATTLE_SCREEN, "Level1.txt");
		else if (isLvl2Clicked)
			Game::setCurrentScreen(constants::BATTLE_SCREEN, "Level2.txt");
		else if (isLvl3Clicked)
			Game::setCurrentScreen(constants::BATTLE_SCREEN, "Level3.txt");
		break;

	case SDL_MOUSEMOTION:
		SDL_GetMouseState(&x, &y);
		BackBtn->onHover(x, y);
		lvl1->onHover(x, y);
		lvl2->onHover(x, y);
		lvl3->onHover(x, y);

		break;
	default:
		break;
	}
}

