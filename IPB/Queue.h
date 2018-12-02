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
	void enqueue(Unit*);
	void pull(Unit*);
	bool checkCollision(Unit*, bool selfDestruct = false);
	void clean();
	void render();
	void move();
	Node* Top();
};
