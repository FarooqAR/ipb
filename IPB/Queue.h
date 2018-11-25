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
	void pull(Player*);
	void checkCollision(Unit*);
	bool checkCollision(Player*);
	void clean();
	void render();
	void move();
};