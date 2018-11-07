#include "pch.h"
#include "Button.h"

Button::Button(LTexture * Texture, string str, int x, int y)
{
	this->word = new Word(str, Texture, x, y);
	this->btnTexture = Texture;
	for (int i = 0; i < 3; i++)
	{
		BtnRect[i].x = 88 * (i + 1);
		BtnRect[i].y = 99 * 5;
		BtnRect[i].w = 88;
		BtnRect[i].h = 99;
	}
	setPosition(x, y);
}
void Button::setText(const char* str)
{
	word->setText(str);
	setPosition(x, y);
}
void Button::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
	this->word->setPosition(x - (word->getTextLength() / 2) * 88
		, y - 99 / 2);
}
void Button::render(SDL_Renderer * gRenderer)
{
	btnTexture->renderTexture(this->x - ((word->getTextLength() / 2) + 1) * 88,
		this->y - 99 / 2, gRenderer, &BtnRect[0]);
	for (int i = 0; i < word->getTextLength(); i++)
	{
		btnTexture->renderTexture(this->x - (word->getTextLength() / 2) * 88
			+ ((i) * 88), this->y - 99 / 2, gRenderer, &BtnRect[1]);
	}
	word->render(gRenderer);
	btnTexture->renderTexture(this->x + (word->getTextLength()) / 2 * 88,
		this->y - 99 / 2, gRenderer, &BtnRect[2]);
}