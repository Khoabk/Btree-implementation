#ifndef ELEM_H
#define ELEM_H

class Btree;

class Bnode;

class Elem{

	int key;

	Elem * prev;

	Elem * next;
	
	Bnode * child;
	
	friend class Btree;
	
	friend class Bnode;
	
	Elem* Insert_between(Elem * Front = nullptr, Elem * Back = nullptr, Bnode * child = nullptr);
	
public:
	
	Elem(int key = 0, Elem * prev = nullptr, Elem * next = nullptr, Bnode * child = nullptr);
	
	~Elem();	
	
};


#endif
