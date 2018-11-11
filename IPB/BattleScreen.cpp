#include "pch.h"
#include "BattleScreen.h"
#include "LTexture.h"
#include <iostream>
using namespace std;

BattleScreen::BattleScreen(SDL_Renderer* renderer): renderer(renderer)
{
	backgroundTexture = new LTexture;
	backgroundTexture->loadFromFile("assets/space.jpg", renderer);
}
BattleScreen::~BattleScreen()
{
	
}
void BattleScreen::render()
{
	backgroundTexture->renderTexture(0, 0, renderer);
	
}
void BattleScreen::handleEvents(SDL_Event& event)
{

}
