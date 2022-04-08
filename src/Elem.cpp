#include "Elem.h"
#include "Bnode.h"



Elem* Elem::Insert_between(Elem * Front, Elem * Back, Bnode * new_child)
{
	prev = Front;
	
	next = Back;
	
	if(new_child != nullptr) child = new_child;
	
	if(prev != nullptr)
	{ 
		prev->next = this;	
	}
	
	if(next != nullptr)
	{
		next->prev = this;
	}
	
	return (Front == nullptr)?this:Front;
}




Elem::Elem(int key, Elem * prev, Elem * next, Bnode * child):key(key), prev(prev), next(next), child(child)
{
	if(prev != nullptr)prev->next = this;

	if(next != nullptr)next->prev = this;	
}




Elem::~Elem()
{
	delete child;
	
	delete next;
}
