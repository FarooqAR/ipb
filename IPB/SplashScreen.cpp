#include "pch.h"
#include <stdio.h>
#include "SplashScreen.h"
#include "LTexture.h"
#include "constants.h"
#include "Button.h"
#include "Game.h"

SplashScreen::SplashScreen(SDL_Renderer* renderer, LTexture* imagesSpriteSheet)
	: renderer(renderer)
{	
	this->imagesSpriteSheet = imagesSpriteSheet;
	frames = 0;
	gameTitle = new Word("Interplanetary Battlefield", imagesSpriteSheet, 0, 300, 1); // 300 here is the starting y coord
	subTitle = new Word("FRAM Studios Copyright 2018", imagesSpriteSheet, 0, 400, 0.5); // 300 here is the starting y coord
	gameTitle->SetXCentered();
	subTitle->SetXCentered();
}
SplashScreen::~SplashScreen()
{
	delete gameTitle;
	delete subTitle;
}

void SplashScreen::Render()
{
	if (frames == constants::SPLASH_DELAY)
		Game::GetInstance()->SetCurrentScreen(constants::MAIN_MENU_SCREEN);
	
	gameTitle->Render(renderer);
	subTitle->Render(renderer);
	frames++;
}


void SplashScreen::HandleEvents(SDL_Event& event)
{	

}