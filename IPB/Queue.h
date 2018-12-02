#pragma once
#include "Node.h"
#include "Unit.h"
#include "Player.h"
#include "EasterEgg.h"
#include <SDL.h>

class Queue
{
private:
	Node* head;
	Node* tail;
public:
	Queue();
	~Queue();
	void enqueue(Unit*);
	void pull(Unit*);
	bool checkCollision(Unit*, bool selfDestruct = false);
	void checkCollision(Queue* queue, LTexture* ExplosionTexture, SDL_Rect(&clip)[20], bool Destroy = false);
	void Collected(Player * player);
	void clean();
	void render();
	void move();
};
