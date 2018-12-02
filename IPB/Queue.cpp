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

void Queue::enqueue(Unit* unit)
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


void Queue::clean()
{
	Node* temp = head;
	while (temp != NULL)
	{
		if (temp->unit->getAlive() == false)
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
bool Queue::checkCollision(Unit* unit, bool selfDestruct)
{
	Node* temp = head;
	bool isColliding = false;
	while (temp != NULL)
	{
		if (temp->unit->checkCollision(unit))
		{
			isColliding = true;
			if (selfDestruct)
				temp->unit->setAlive(false);
		}
		temp = temp->next;
	}
	return isColliding;
}

void Queue::render()
{
	Node* temp = head;
	while (temp != NULL)
	{
		temp->unit->render();
		temp = temp->next;
	}
}


//pulls hero towards all of the planets
void Queue::pull(Unit* player)
{
	Node* temp = head;
	while (temp != NULL)
	{
		//applies gravity for temp planet
		((Attractor*)temp->unit)->gravForce(player);
		temp = temp->next;
	}

}
void Queue::move()
{
	Node* temp = head;
	while (temp != NULL)
	{
		temp->unit->move();
		temp = temp->next;
	}
}
