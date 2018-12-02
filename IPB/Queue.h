#pragma once
#include "Node.h"
#include "Unit.h"
#include "Player.h"
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
	void Clean();
	void Render();
	void Move();
	Node* Top();
};
