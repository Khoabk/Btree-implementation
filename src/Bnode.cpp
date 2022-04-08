#include "Bnode.h"
#include <iostream>

using namespace std;


Elem * Bnode::Delete_from_list(Elem * deleted_elem, bool mode)
{
	num--;

	if(deleted_elem == nullptr) throw(-11);
	
	// mid pointer handling
	
	if(mid != nullptr && deleted_elem->key <= mid->key) mid = mid->next;

	// head pointer handling

	if(head == deleted_elem) head = head->next;
	
	// tail pointer handling
	
	if(tail == deleted_elem) tail = tail->prev;
	
	// separating process
	
	if(deleted_elem->next != nullptr) deleted_elem->next->prev = deleted_elem->prev;
	
	if(deleted_elem->prev != nullptr) deleted_elem->prev->next = deleted_elem->next;
	
	deleted_elem->next = nullptr;
	
	deleted_elem->prev = nullptr;
	
	if(mode){ delete deleted_elem; deleted_elem = nullptr;}
	
	return deleted_elem;
}




void Bnode::Replace_node(Elem * replaced_elem, Elem * substitution_elem)
{
	if(replaced_elem == nullptr || substitution_elem == nullptr) throw(-10);
	
	if(mid == replaced_elem) mid = substitution_elem; // mid pointer handling
	
	substitution_elem->child = replaced_elem->child;
	
	replaced_elem->child = nullptr;
	
	substitution_elem->next = replaced_elem->next;
	
	if(replaced_elem->next != nullptr)
	{
		replaced_elem->next->prev = substitution_elem;
		
		replaced_elem->next = nullptr;
	}
	
	else tail = substitution_elem; //tail pointer handling
	
	substitution_elem->prev = replaced_elem->prev;
	
	if(replaced_elem->prev != nullptr) 
	{
		replaced_elem->prev->next = substitution_elem;
		
		replaced_elem->prev = nullptr;
	}
	
	else head = substitution_elem; //head pointer handling
	
	replaced_elem->prev = nullptr;
	
	delete replaced_elem;
}





void Bnode::Add_to_list(Elem * ptr, bool front_back)
{
	if(ptr == nullptr) throw(-8);

	num++;

	//Add to front
	if(front_back)
	{
		ptr->next = head;
		
		if(head == nullptr) tail = ptr;
		
		else ptr->next->prev = ptr;
		
		head = ptr;
	
		if(mid != nullptr) mid = mid->prev;
		
		else if(num == degree/2) mid = tail;
		
		return;
	}

	//Add to back
	if(tail == nullptr){
	
		head = ptr;
		
		tail = ptr;
	
		ptr->next = nullptr;
	}

	else{
		tail->next = ptr;
		
		ptr->next = nullptr;
		
		ptr->prev = tail;
		
		tail = ptr;
	}
	
	
	if(num == degree/2) mid = tail;
}








Elem * Bnode::Split()
{
	//obtain the middle element
	Elem * mid_elem = mid->next;

	//create left child
	Bnode * left_child = new Bnode(0,leaf,degree,num/2,head,mid,mid_elem->child);
	
	//this is root node thus not return any key
	if(root)
	{
		//create right child
		Bnode * right_child = new Bnode(0,leaf,degree,num - 1 - num/2,mid_elem->next,tail,upper_bound);
		
		head = mid_elem->Insert_between();
		
		tail = head;
		
		num = 1;
		
		mid = (num == degree/2)? tail: nullptr;
		
		mid_elem->child = left_child;
		
		upper_bound = right_child;
		
		leaf = 0;
		
		return nullptr;
	}
	
	//this is not root node thus return the middle key
	head = mid_elem->next;
	
	head = head->Insert_between(nullptr,head->next);
	
	num = num - 1 - num/2;
	
	if(num == degree/2)mid = tail; 
	
	else mid = nullptr;
	
	return mid_elem->Insert_between(nullptr,nullptr,left_child);
}







Elem * Bnode::Insert_handler(Elem * carry, Elem * hook)
{
	//Check if list is empty or carry should be inserted at the end
	
	if(hook == nullptr)
	{
		// list is empty
		if(head == nullptr)
		{
			head = carry;
			
			tail = head;
		}
		// hook is at the end	
		else
		{
			carry->Insert_between(tail,nullptr);
			
			tail = carry;
		}
	}
	
	//carry should be inserted somewhere between head and before tail
	
	else
	{
		// should be inserted before head
		if(hook->prev == nullptr)
		{
			head = carry->Insert_between(nullptr,head);
		}
		//should be inserted some where in between head and tail
		else
		{
			carry->Insert_between(hook->prev,hook);
		}
	}
	
	//carry out some manipulations to preserve the btree's property
	
	num++;
	
	if(mid != nullptr)
	{
		if(carry->key < mid->key)mid = mid->prev;
	}
	
	else if(num == degree/2)mid = tail;
	
	if(num == degree) return Split();	
	
	return nullptr;
}






Elem * Bnode::Insert(int key, bool & exists)
{
	Elem * temp = head;
	
	while(1)
	{
		if(temp == nullptr || key < temp->key)
		{
			if(leaf)
			{	
				exists = false;
			
				Elem * elem_Carry = new Elem(key);
				
				return Insert_handler(elem_Carry, temp);
			}
			
			Elem * elem_Temp = (temp == nullptr)?upper_bound->Insert(key,exists):temp->child->Insert(key, exists);
			
			if(elem_Temp != nullptr)
			{
				return Insert_handler(elem_Temp,temp);
			}
			
			return nullptr;
		}
		
		
		if(key == temp->key){
		
		exists = true;
		
		return nullptr;
		
		}
		
		temp = temp->next;
	}
}





Bnode::Bnode(int root, int leaf, int degree, int num, Elem * h, Elem * t, Bnode * uppb):root(root), leaf(leaf), degree(degree), num(num), head(h), tail(t), upper_bound(uppb)
{
	
	if(num == degree/2)mid = tail;
	
	else mid = nullptr;
	
	if(tail != nullptr) tail->next = nullptr;
	
	if(head != nullptr) head->prev = nullptr;

}



Bnode::~Bnode()
{
	delete head;
	
	delete upper_bound;
}
