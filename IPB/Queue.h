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
	void Enqueue(Unit*);
	void Pull(Unit*);
	bool CheckCollision(Unit*, bool selfDestruct = false);
	void CheckCollision(Queue* queue, LTexture* ExplosionTexture, SDL_Rect(&clip)[20], bool Destroy = false);
	void Collected(Player * player);
	void Clean();
	void Render();
	void Move();
	Node* Top();
};
