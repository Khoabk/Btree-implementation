#ifndef BTREE_H
#define BTREE_H


#include "Bnode.h"

#include <iostream>


class Btree{

	Bnode * root;
	
	int degree;
	
	int num;
	
// Delettion assistance methods

// 4th level function	

	int Merge(Bnode ** subjected_Bnode, Elem * critical_elem);
	
	int Delete_handler(Bnode ** subjected_Bnode, Elem * critical_elem);
	
// 3rd level function	

	int Find_right_sibling(Bnode * subjected_Bnode, Elem * critical_elem);

	int Find_left_sibling(Bnode * subjected_Bnode, Elem * critical_elem);
	
	int Find_node(Bnode ** subjected_Bnode, Elem * & get_Elem, bool mode); // mode == true -> obtain inorder successor, mode == false -> obtain inorder predecessor
	
// 2nd level function	
	
	int Internal_node_handler(Bnode ** subjected_Bnode, Elem * deleted_elem);
	
// 1st level function
	
	int Delete_node(Bnode ** subjected_Bnode, int key);
	
// Display assistance methods	
	
	int get_height(Bnode * ptr);

	void Print_Bnode(Bnode * node, int level, bool last_elem);
	
	void Print_Bnode_FSM(Bnode * node);
	
public:

	Btree(int degree);
	
	~Btree(){ std::cout<<"Destroy Btree\n";    delete root; }
	
	bool Insert(int key);

	bool Delete(int key);
	
	void Print_Btree();

};




#endif
