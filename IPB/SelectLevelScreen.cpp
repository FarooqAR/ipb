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
	backBtn = new Button(imagesSpriteSheet, "Back", x, 250 + 65 * 3);

	string title = "Select Level";
	screenTitle = new Word(title, imagesSpriteSheet, 0, 300, 1); // 300 here is the starting y coord
	screenTitle->SetXCentered();
}

SelectLevelScreen::~SelectLevelScreen()
{
}

void SelectLevelScreen::Render()
{
	screenTitle->Render(renderer);
	double y = screenTitle->GetY();
	if (screenTitle->GetY() > 100) // handle animation; move the title to y=100
		y = screenTitle->GetY() * 0.9;
	else
	{
		lvl1->Render(renderer);
		lvl2->Render(renderer);
		lvl3->Render(renderer);
		backBtn->Render(renderer);
	}

	screenTitle->SetPosition(screenTitle->GetX(), (int)y);
}


void SelectLevelScreen::HandleEvents(SDL_Event& event)
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
		backBtn->OnClickDown(x, y);
		lvl1->OnClickDown(x, y);
		lvl2->OnClickDown(x, y);
		lvl3->OnClickDown(x, y);
		break;

	case SDL_MOUSEBUTTONUP:

		SDL_GetMouseState(&x, &y);
		isBackBtnClicked = backBtn->OnClickUp(x, y);
		isLvl1Clicked = lvl1->OnClickUp(x, y);
		isLvl2Clicked = lvl2->OnClickUp(x, y);
		isLvl3Clicked = lvl3->OnClickUp(x, y);
		if (isBackBtnClicked)
			Game::GetInstance()->SetCurrentScreen(constants::MAIN_MENU_SCREEN);
		if (isLvl1Clicked)
			Game::GetInstance()->SetCurrentScreen(constants::BATTLE_SCREEN, "Level1.txt");
		else if (isLvl2Clicked)
			Game::GetInstance()->SetCurrentScreen(constants::BATTLE_SCREEN, "Level2.txt");
		else if (isLvl3Clicked)
			Game::GetInstance()->SetCurrentScreen(constants::BATTLE_SCREEN, "Level3.txt");
		break;

	case SDL_MOUSEMOTION:
		SDL_GetMouseState(&x, &y);
		backBtn->OnHover(x, y);
		lvl1->OnHover(x, y);
		lvl2->OnHover(x, y);
		lvl3->OnHover(x, y);

		break;
	default:
		break;
	}
}

