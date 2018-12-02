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
	title->SetXCentered();
	thrustLabel = new Word("Thrust", imagesSpriteSheet, x, 150, 0.5);
	thrustLabel->SetXCentered();
	upBtn = new Button(imagesSpriteSheet, "UP", x / 2, 200, 90);
	goBtn = new Button(imagesSpriteSheet, "GO!", x / 2, 550, 90);
	spaceBtn = new Button(imagesSpriteSheet, "SPACEBAR", (constants::WINDOW_WIDTH - constants::BUTTON_WIDTH) / 2, 400);
	x -= 30;
	leftBtn = new Button(imagesSpriteSheet, "LEFT", x / 2 - 150, 300, 120);
	rightBtn = new Button(imagesSpriteSheet, "RIGHT", x / 2 + 150, 300, 120);
	turnLeftLabel = new Word("Turn Left", imagesSpriteSheet, 120, 310, 0.5);
	turnRightLabel = new Word("Turn Right", imagesSpriteSheet, 750, 310, 0.5);
	shootLabel = new Word("Shoot", imagesSpriteSheet, 0, 450, 0.5);
	shootLabel->SetXCentered();
}

ControlsIntroScreen::~ControlsIntroScreen()
{
	delete upBtn;
	delete goBtn;
	delete leftBtn;
	delete spaceBtn;
	delete rightBtn;
	delete turnLeftLabel;
	delete turnRightLabel;
	delete thrustLabel;
	delete title;
	delete shootLabel;
}

void ControlsIntroScreen::Render()
{
	upBtn->Render(renderer);
	leftBtn->Render(renderer);
	spaceBtn->Render(renderer);
	rightBtn->Render(renderer);
	goBtn->Render(renderer);
	turnLeftLabel->Render(renderer);
	turnRightLabel->Render(renderer);
	thrustLabel->Render(renderer);
	shootLabel->Render(renderer);
	title->Render(renderer);
}

void ControlsIntroScreen::HandleEvents(SDL_Event & event)
{
	int x, y;
	bool isGoBtnClicked = false;
	SDL_GetMouseState(&x, &y);
	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		goBtn->OnClickDown(x, y);

		break;
	case SDL_MOUSEBUTTONUP:
		isGoBtnClicked = goBtn->OnClickUp(x, y);
		if (isGoBtnClicked)
			Game::SetCurrentScreen(constants::BATTLE_SCREEN);

		break;
	case SDL_MOUSEMOTION:
		goBtn->OnHover(x, y);
		break;
	default:
		break;
	}
}
