#ifndef BNODE_H
#define BNODE_H

#include "Elem.h"


class Bnode{

	friend class Btree;

	int root;
	
	int leaf;
	
	int degree;
	
	int num;
	
	Elem * head;
	
	Elem * mid;
	
	Elem * tail;
	
	Bnode * upper_bound;

// Deletion assistance methods	
	
	void Replace_node(Elem * replaced_elem, Elem * substitution_elem);
	
	Elem * Delete_from_list(Elem * trv, bool mode); // True -> delete and return null, False -> remove elem from list and return pointer
	
	void Add_to_list(Elem * ptr, bool front_back); // True -> front, False -> back
	
// Insertion assistance methods	
	
	Elem * Insert(int key, bool & exist);
	
	Elem * Insert_handler(Elem* keyin, Elem * hook);
	
	Elem * Split();
	
public:
	
	Bnode(int root = 0, int leaf = 0, int degree = 3, int num = 0, Elem * h = nullptr, Elem * t = nullptr, Bnode * uppb = nullptr);
	
	~Bnode();
	
};


#endif
