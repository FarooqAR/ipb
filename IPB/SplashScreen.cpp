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
	gameTitle->setXCentered();
	subTitle->setXCentered();
}
SplashScreen::~SplashScreen()
{
	delete gameTitle;
	delete subTitle;
}

void SplashScreen::render()
{
	if (frames == 120)
		Game::setCurrentScreen(constants::MAIN_MENU_SCREEN);
	
	gameTitle->render(renderer);
	subTitle->render(renderer);
	frames++;
}


void SplashScreen::handleEvents(SDL_Event& event)
{	

}