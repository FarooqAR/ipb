#pragma once
#include "Game.h"
#include "Point.h"
#include "LTexture.h"

enum MOTION { RIGHT, LEFT, UP, DOWN };
class Unit
{
public:
	Unit();
	Unit(SDL_Renderer* renderer, LTexture* unitTexture, float scale, bool alive, double angle);
	~Unit();
	void setAlive(bool);
	bool getAlive();
	bool checkCollision(Unit* unit);
	bool checkCollision(Unit* unit, bool isCentered);
	void setPosition(int x, int y);
	Point getPosition();
	int getWidth();
	int getHeight();
	void setAngle(double);
	double getAngle();
	virtual void move();
	void move(int direction); 
	virtual void render();
	float speedX; // make protected!
	float speedY; // make protected!
	void setScale(float scale);
	float getScale();

protected:
	Point position;
	LTexture * objTexture;
	bool alive;
	int width;
	int height;
	double angle;
	float scale;
	float speedXdecimal;
	float speedYdecimal;
	int count1 = 0;
	float thrust = .0355;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;

};
