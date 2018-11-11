#include "pch.h"
#include <stdio.h>
#include "MainMenuScreen.h"
#include "LTexture.h"
#include "constants.h"
#include "Button.h"


MainMenuScreen::MainMenuScreen(SDL_Renderer* renderer): renderer(renderer)
{
	alphabetsSpriteSheet = new LTexture;
	buttonSpriteSheet = new LTexture;

	alphabetsSpriteSheet->loadFromFile("assets/spries.png", renderer, 1, 0, 0, 0);
	buttonSpriteSheet->loadFromFile("assets/button_sprite.png", renderer);
	int x = (constants::WINDOW_WIDTH - buttonSpriteSheet->getWidth()) / 2;
	startGameBtn = new Button(buttonSpriteSheet, alphabetsSpriteSheet, "Start Game", x, 200);
	loadGameBtn = new Button(buttonSpriteSheet, alphabetsSpriteSheet, "Load Game", x, 200 + 65);
	selectLevelBtn = new Button(buttonSpriteSheet, alphabetsSpriteSheet, "Select Level", x, 200 + 65*2);
	quitGameBtn = new Button(buttonSpriteSheet, alphabetsSpriteSheet, "Quit Game", x, 200 + 65 * 3);
	
	string title = "Interplanetory Battlefield";
	gameTitle = new Word(title, alphabetsSpriteSheet, 0, 300, 1); // 300 here is the starting y coord
	gameTitle->setXCentered();
}
void MainMenuScreen::render()
{
	gameTitle->render(renderer);
	double y = gameTitle->getY();
	if (gameTitle->getY() > 100) 
		y = gameTitle->getY() * 0.9;
	else
	{
		// This is just for demo, we need to render Buttons
		/*int x = (constants::WINDOW_WIDTH - startGameBtn->getWidth()) / 2;*/
		startGameBtn->render(renderer);
		loadGameBtn->render(renderer);
		selectLevelBtn->render(renderer);
		quitGameBtn->render(renderer);
	}

	gameTitle->setPosition(gameTitle->getX(), y);
}
void MainMenuScreen::handleEvents(SDL_Event& event)
{

}