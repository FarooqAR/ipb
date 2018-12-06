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
	bool CheckCollision(Unit*, bool selfDestruct = false, bool explode = false);
	void CheckCollision(Queue* queue);
	void Collected(Player * player);
	void Clean();
	void Render();
	void Move();
	Node* Top();
};
