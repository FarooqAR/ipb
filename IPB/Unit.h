#pragma once
#include "Point.h"
#include "LTexture.h"

enum MOTION { RIGHT, LEFT, UP, DOWN };
class Unit
{
public:
	Unit();
	Unit(SDL_Renderer* renderer, LTexture* unitTexture, float scale, bool alive, double angle);
	~Unit();
	void SetAlive(bool);
	bool GetAlive();
	bool CheckCollision(Unit* unit);
	bool CheckCollision(Unit* unit, bool isCentered);
	void SetPosition(int x, int y);
	Point GetPosition();
	int GetWidth();
	int GetHeight();
	void SetAngle(double);
	double GetAngle();
	virtual void Move();
	void Move(int direction); 
	virtual void Render();
	void SetScale(float scale);
	void SetClip(SDL_Rect);
	float GetScale();
	void SetSpeed(float x, float y);
	float GetXSpeed();
	float GetYSpeed();

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
	float thrust = .0355f;
	float speedX; 
	float speedY; 
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;

};
