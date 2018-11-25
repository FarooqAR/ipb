#pragma once
#include "Game.h"
#include "Point.h"
#include "LTexture.h"

enum MOTION { RIGHT, LEFT, UP, DOWN };
class Unit
{
public:
	Unit();
	~Unit();
	void setAlive(bool);
	bool getAlive();
	bool checkCollision(Unit* unit);
	void setPosition(int x, int y);
	Point getPosition();
	int getWidth();
	int getHeight();
	void setAngle(double);
	double getAngle();
	void move();
	void move(int direction); 
	virtual void render();
	float speedX;
	float speedY;

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
