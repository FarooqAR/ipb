#include "pch.h"
#include "constants.h"
#include "Button.h"
#include "Point.h"
#include "Game.h"

Button::Button()
{
	this->label = nullptr;
}
Button::Button(LTexture * bgTexture, LTexture * alphabetsSpriteSheet, string label, int x, int y, int w, int h)
{
	width = w;
	height = h;
	spriteIndex = 0;
	this->btnTexture = bgTexture;
	float labelScale = 0.7f;
	int labelX = (int) (width - label.length() * 60 * labelScale + (label.length() - 1) * 30 * labelScale);
	this->label = new Word(
		label,
		alphabetsSpriteSheet,
		x + labelX / 2,
		y,
		labelScale
	);
	SetPosition(x, y);
}

Button::Button(LTexture * imagesSpriteSheet, string label, int x, int y, int w, int h)
{
	width = w;
	height = h;
	Point spritePos = constants::BUTTONS_SPRITE_START_POSITION;
	spriteClips[0] = { spritePos.x, spritePos.y, constants::BUTTON_WIDTH, constants::BUTTON_HEIGHT };
	spriteClips[1] = { spritePos.x, spritePos.y + 56, constants::BUTTON_WIDTH, constants::BUTTON_HEIGHT };
	spriteClips[2] = { spritePos.x, spritePos.y + 109, constants::BUTTON_WIDTH, constants::BUTTON_HEIGHT };
	spriteIndex = 0;
	this->btnTexture = imagesSpriteSheet;
	float labelScale = 0.7f;
	int labelX = (int) (width - label.length() * 60 * labelScale + (label.length() - 1) * 30 * labelScale);
	this->label = new Word(
		label,
		imagesSpriteSheet,
		x + labelX / 2,
		y,
		labelScale
	);
	SetPosition(x, y);
}

void Button::Render(SDL_Renderer * gRenderer)
{
	this->btnTexture->RenderTexture(
		this->position.x,
		this->position.y,
		gRenderer,
		&spriteClips[spriteIndex],
		SDL_FLIP_NONE,
		0.0,
		nullptr,
		(float)width / (float)constants::BUTTON_WIDTH,
		(float)height / (float)constants::BUTTON_HEIGHT
	);
	this->label->Render(gRenderer);
}

void Button::SetPosition(int x, int y)
{
	this->position.x = x;
	this->position.y = y;
}

void Button::OnHover(int clickX, int clickY)
{

	if (clickX >= position.x &&
		clickX <= position.x + width &&
		clickY >= position.y &&
		clickY <= position.y + height)
	{
		if (spriteIndex == 0)
			Game::GetInstance()->PlayMusic(constants::MUSIC_BTN_HOVER);
		spriteIndex = 1;
	}
	else
		spriteIndex = 0;
}
void Button::OnClickDown(int clickX, int clickY)
{
	if (clickX >= position.x &&
		clickX <= position.x + width &&
		clickY >= position.y &&
		clickY <= position.y + height)
	{
		spriteIndex = 2;
		Game::GetInstance()->PlayMusic(constants::MUSIC_BTN_CLICK);
	}
}
bool Button::OnClickUp(int clickX, int clickY)
{
	if (clickX >= position.x &&
		clickX <= position.x + width &&
		clickY >= position.y &&
		clickY <= position.y + height)
	{
		/*if (spriteIndex == 0)*/
		Game::GetInstance()->PlayMusic(constants::MUSIC_BTN_CLICK);
		spriteIndex = 1;
		return true;
	}
	return false;
}
Button::~Button()
{
}
