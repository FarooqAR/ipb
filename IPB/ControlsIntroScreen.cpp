#include "pch.h"
#include "ControlsIntroScreen.h"
#include "Button.h"
#include "Word.h"
#include "Game.h"

ControlsIntroScreen::ControlsIntroScreen(SDL_Renderer * gRenderer, LTexture * imagesSpriteSheet)
	: renderer(gRenderer)
{
	this->imagesSpriteSheet = imagesSpriteSheet;
	int x = constants::WINDOW_WIDTH - 90;
	title = new Word("Controls", imagesSpriteSheet, x, 30);
	title->setXCentered();
	thrustLabel = new Word("Thrust", imagesSpriteSheet, x, 150, 0.5);
	thrustLabel->setXCentered();
	upBtn = new Button(imagesSpriteSheet, "UP", x / 2, 200, 90);
	goBtn = new Button(imagesSpriteSheet, "GO!", x / 2, 550, 90);
	x -= 30;
	leftBtn = new Button(imagesSpriteSheet, "LEFT", x / 2 - 150, 300, 120);
	rightBtn = new Button(imagesSpriteSheet, "RIGHT", x / 2 + 150, 300, 120);
	turnLeftLabel = new Word("Turn Left", imagesSpriteSheet, 120, 310, 0.5);
	turnRightLabel = new Word("Turn Right", imagesSpriteSheet, 750, 310, 0.5);
}

ControlsIntroScreen::~ControlsIntroScreen()
{
	delete upBtn;
	delete goBtn;
	delete leftBtn;
	delete rightBtn;
	delete turnLeftLabel;
	delete turnRightLabel;
	delete thrustLabel;
	delete title;
}

void ControlsIntroScreen::render()
{
	upBtn->render(renderer);
	leftBtn->render(renderer);
	rightBtn->render(renderer);
	goBtn->render(renderer);
	turnLeftLabel->render(renderer);
	turnRightLabel->render(renderer);
	thrustLabel->render(renderer);
	title->render(renderer);
}

void ControlsIntroScreen::handleEvents(SDL_Event & event)
{
	int x, y;
	bool isGoBtnClicked = false;
	SDL_GetMouseState(&x, &y);
	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		goBtn->onClickDown(x, y);

		break;
	case SDL_MOUSEBUTTONUP:
		isGoBtnClicked = goBtn->onClickUp(x, y);
		if (isGoBtnClicked)
			Game::setCurrentScreen(constants::BATTLE_SCREEN);

		break;
	case SDL_MOUSEMOTION:
		goBtn->onHover(x, y);
		break;
	default:
		break;
	}
}
