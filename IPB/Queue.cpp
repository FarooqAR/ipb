#include "pch.h"
#include "Queue.h"
#include "Attractor.h"

Queue::Queue()
{
	head = NULL;
	tail = NULL;
}


Queue::~Queue()
{
	while (head != NULL)
	{
		Node* temp = head;
		head = head->next;
		delete temp;
	}
}

void Queue::Enqueue(Unit* unit)
{
	if (head == NULL)
	{
		head = new Node;
		head->unit = unit;
		head->next = NULL;
		head->prev = NULL;
		tail = head;
	}
	else
	{
		tail->next = new Node;
		tail->next->unit = unit;
		tail->next->next = NULL;
		tail->next->prev = tail;
		tail = tail->next;
	}
}


void Queue::Clean()
{
	Node* temp = head;
	while (temp != NULL)
	{
		if (temp->unit->GetAlive() == false)
		{
			if (temp->prev == NULL)
			{
				head = head->next;
				if (head != NULL)
				{
					head->prev = NULL;
				}
				delete temp;
				temp = head;
			}
			else if (temp->next == NULL)
			{
				tail = tail->prev;
				tail->next = NULL;
				delete temp;
				break;
			}
			else
			{
				Node* carry = temp->next;
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				delete temp;
				temp = carry;
			}
		}
		if (temp != nullptr)
			temp = temp->next;
	}
}
bool Queue::CheckCollision(Unit* unit, bool selfDestruct)
{
	Node* temp = head;
	bool isColliding = false;
	while (temp != NULL)
	{
		if (temp->unit->CheckCollision(unit))
		{
			isColliding = true;
			if (selfDestruct)
				temp->unit->SetAlive(false);
		}
		temp = temp->next;
	}
	return isColliding;
}

void Queue::Render()
{
	Node* temp = head;
	while (temp != NULL)
	{
		temp->unit->Render();
		temp = temp->next;
	}
}


//pulls hero towards all of the planets
void Queue::Pull(Unit* player)
{
	Node* temp = head;
	while (temp != NULL)
	{
		//applies gravity for temp planet
		((Attractor*)temp->unit)->GravForce(player);
		temp = temp->next;
	}

}
void Queue::Move()
{
	Node* temp = head;
	while (temp != NULL)
	{
		temp->unit->Move();
		temp = temp->next;
	}
}

//compares objects of one queue with objects of another for collision detection
void Queue::checkCollision(Queue* queue, LTexture* ExplosionTexture, SDL_Rect(&clip)[20], bool Destory)
{
	Node* temp = head;
	while (temp != NULL)
	{
		if (queue->checkCollision(temp->unit, Destory))
		{
			temp->unit->setAlive(false);
			temp->unit->Explosion(ExplosionTexture, clip, temp->unit);
		}
		temp = temp->next;
	}
}


void Queue::Collected(Player* player)
{
	Node* temp = head;
	while (temp != NULL)
	{
		if (temp->unit->getAlive() == false)
		{
			((EasterEgg*)temp->unit)->HasCollected(player);
		}
		temp = temp->next;
	}
}

Node * Queue::Top()
{
	return head;
}