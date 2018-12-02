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
	screenTitle = new Word(title, imagesSpriteSheet, 10, 300); 
	screenTitle->SetXCentered();
}

LoadGameScreen::~LoadGameScreen()
{
}
void LoadGameScreen::Render()
{
	screenTitle->Render(renderer);
	double y = screenTitle->GetY();
	if (screenTitle->GetY() > 100) // handle animation; move the title to y=100
		y = screenTitle->GetY() * 0.9;
	else
	{
		selectSaved1Btn->Render(renderer);
		selectSaved2Btn->Render(renderer);
		selectSaved3Btn->Render(renderer);
		backBtn->Render(renderer);
	}

	screenTitle->SetPosition(screenTitle->GetX(), (int)y);
}


void LoadGameScreen::HandleEvents(SDL_Event& event)
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
		selectSaved1Btn->OnClickDown(x, y);
		selectSaved2Btn->OnClickDown(x, y);
		selectSaved3Btn->OnClickDown(x, y);
		backBtn->OnClickDown(x, y);

		break;
	case SDL_MOUSEBUTTONUP:

		SDL_GetMouseState(&x, &y);
		is1Clicked = selectSaved1Btn->OnClickUp(x, y);
		is2Clicked = selectSaved2Btn->OnClickUp(x, y);
		is3Clicked = selectSaved3Btn->OnClickUp(x, y);
		isBackClicked = backBtn->OnClickUp(x, y);
		
		if (isBackClicked)
			Game::SetCurrentScreen(constants::MAIN_MENU_SCREEN);
		else if (is1Clicked)
			Game::SetCurrentScreen(constants::SAVE_GAME_SCREEN, "SavedGame1.txt");
		else if (is2Clicked)
			Game::SetCurrentScreen(constants::SAVE_GAME_SCREEN, "SavedGame2.txt");
		else if (is3Clicked)
			Game::SetCurrentScreen(constants::SAVE_GAME_SCREEN, "SavedGame3.txt");
		break;
	case SDL_MOUSEMOTION:
		SDL_GetMouseState(&x, &y);
		selectSaved1Btn->OnHover(x, y);
		selectSaved2Btn->OnHover(x, y);
		selectSaved3Btn->OnHover(x, y);
		backBtn->OnHover(x, y);
		break;
	default:
		break;
	}
}