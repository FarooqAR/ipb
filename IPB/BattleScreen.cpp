#include "pch.h"
#include "BattleScreen.h"
#include "TextureManager.h"
#include <iostream>
using namespace std;

BattleScreen::BattleScreen(SDL_Renderer* renderer): renderer(renderer)
{
	backgroundTexture = TextureManager::LoadTexture("assets/space.jpg", renderer);
}
BattleScreen::~BattleScreen()
{
	
}
void BattleScreen::render()
{
	SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
	
}
void BattleScreen::handleEvents(SDL_Event& event)
{

}
