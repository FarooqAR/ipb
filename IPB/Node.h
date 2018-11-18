#pragma once
#include"Unit.h"

struct Node
{
	Unit* unit;
	Node* next;
	Node* prev;

	~Node()
	{
		delete unit;
	}
};
