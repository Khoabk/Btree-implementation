#include "Btree.h"
//#include "Queue.h"
#include "Queue.cpp"
#include <iostream>
#include <math.h>


using namespace std;




Btree::Btree(int degree):root(nullptr),degree(degree),num(0)
{
	if(degree < 3)degree = 3;
	
	cout<<"the degree is: "<<degree<<endl;
}





int Btree::Merge(Bnode ** subjected_Bnode, Elem * critical_elem)
{
	if((*subjected_Bnode) == nullptr) return -1;
	
	Bnode * merged_Bnode;
	
	merged_Bnode = (critical_elem == nullptr)? (*subjected_Bnode)->upper_bound: (critical_elem->next == nullptr)? (*subjected_Bnode)->upper_bound: critical_elem->next->child;
	
	critical_elem = (critical_elem == nullptr)?(*subjected_Bnode)->Delete_from_list((*subjected_Bnode)->tail, false):(*subjected_Bnode)->Delete_from_list(critical_elem, false);
	
	Bnode * co_merged_Bnode = critical_elem->child;
	
	if(co_merged_Bnode == nullptr) throw(-7);
	
	critical_elem->child = co_merged_Bnode->upper_bound;
	
	co_merged_Bnode->upper_bound = nullptr;
	
	merged_Bnode->Add_to_list(critical_elem,true);
	
	while(co_merged_Bnode->num > 0) merged_Bnode->Add_to_list(co_merged_Bnode->Delete_from_list(co_merged_Bnode->tail,false),true);
	
	delete co_merged_Bnode;	
	
	if((*subjected_Bnode)->root == 1 && (*subjected_Bnode)->num == 0)
	{
		Bnode * get = (*subjected_Bnode);
		
		(*subjected_Bnode) = (*subjected_Bnode)->upper_bound;
		
		(*subjected_Bnode)->root = 1;
		
		get->upper_bound = nullptr;
		
		delete get;
		
		return 1;
	}
	
	if((*subjected_Bnode)->num < (*subjected_Bnode)->degree /2) return 0;

	return 1;
}



int Btree::Find_left_sibling(Bnode * subjected_Bnode, Elem * critical_elem)
{
	// Check input validity
 
	if(subjected_Bnode == nullptr || critical_elem == nullptr) throw -3;

	// Get element from left child		

	Bnode * get_Bnode = critical_elem->child;

	if(get_Bnode == nullptr) throw(-4);

	if(get_Bnode->num == get_Bnode->degree / 2 + get_Bnode->degree % 2 -1) return 0;

	// Swap right most child node with second right most child

	Bnode * bridge_ptr = get_Bnode->upper_bound;

	//if(bridge_ptr == nullptr) throw(-5);

	Elem * get_Elem = get_Bnode->Delete_from_list(get_Bnode->tail, false);
	
	get_Bnode->upper_bound = get_Elem->child; 

	get_Elem->child = bridge_ptr;

	// Swap value of get_Elem->key with the value of critical->key

	int bridge = get_Elem->key;

	get_Elem->key = critical_elem->key;

	critical_elem->key = bridge;

	// Find critical node and re insert get_Elem

	Bnode * critical_node = (critical_elem->next == nullptr)? subjected_Bnode->upper_bound: critical_elem->next->child;

	critical_node->Add_to_list(get_Elem, true);	

	return 1;
}




int Btree::Find_right_sibling(Bnode * subjected_Bnode, Elem * critical_elem)
{
	// Check input validity
	
	if(subjected_Bnode == nullptr) throw(-3);
	
	// Get element from right child
	
	Elem * prev_Elem = (critical_elem == nullptr)? subjected_Bnode->tail: critical_elem->prev;

	Bnode * get_Bnode = (critical_elem == nullptr)? subjected_Bnode->upper_bound: critical_elem->child;
	
	if(get_Bnode == nullptr) throw(-4);

	if(get_Bnode->num == get_Bnode->degree / 2 + get_Bnode->degree % 2 -1) return 0;

	Elem * get_Elem = get_Bnode->Delete_from_list(get_Bnode->head, false);

	// Swap value with parent node
	
	int bridge = prev_Elem->key;

	prev_Elem->key = get_Elem->key;
	
	get_Elem->key = bridge;

	//Find critical node and re-insert the element to the left child

	Bnode * critical_Node = prev_Elem->child;
	
	if(critical_Node == nullptr) throw(-5);
	
	Bnode * Bridge_ptr = critical_Node->upper_bound;

	critical_Node->upper_bound = get_Elem->child;

	get_Elem->child = Bridge_ptr;

	critical_Node->Add_to_list(get_Elem, false);

	return 1;	
}






int Btree::Delete_handler(Bnode ** subjected_Bnode, Elem * subjected_Elem)
{
	if((*subjected_Bnode) == nullptr) return -1;
	
	int state = 0;
	
// First check if the node is to the most right 

	if(subjected_Elem == nullptr) state = 1;
	
	while(1)
	{
		switch(state)
		{
			// Find right sibling	
							
			case 0:
			{
				if(Find_right_sibling(*subjected_Bnode, subjected_Elem->next) == 1) return 1;
				
				if(subjected_Elem->prev == nullptr) state = 2;
				
				else state = 1;
				
				break;
			}
		
			// Find left sibling
			
			case 1:
			{
				Elem * get_Elem = (subjected_Elem == nullptr)? (*subjected_Bnode)->tail: subjected_Elem->prev;
				
				if(Find_left_sibling(*subjected_Bnode, get_Elem) == 1) return 1;
				
				state = 2;
				
				break;
			}
			
		   	// If not left nor right sibling is found then merge the node with its parent node
		   	
		   	case 2:
		   	{
		   		return Merge(subjected_Bnode, subjected_Elem);
		   	}
		   	
		   	default: return -1;
		}
			
	}

}



int Btree::Find_node(Bnode ** subjected, Elem * & get_Node, bool mode)
{
	if((*subjected) == nullptr) return -1;
	
	if((*subjected)->leaf == 1)
	{
		if(mode && (*subjected)->num == (*subjected)->degree / 2 + (*subjected)->degree %2 -1) return 2;
		
		Elem * get = (mode)? (*subjected)->head : (*subjected)->tail;
		
		get_Node = (*subjected)->Delete_from_list(get, false);
		
		if(!mode && (*subjected)->num < (*subjected)->degree / 2 + (*subjected)->degree %2 -1) return 0;
		
		return 1;
	}

	int code; 
	
	Elem * get = nullptr;
	
	if(mode)
	{
		get = (*subjected)->head;
		
		code = Find_node(&(get->child), get_Node, mode);	
	}
	
	else code = Find_node(&((*subjected)->upper_bound), get_Node, mode);
	
	if(code == 1 || code == 2 || code == -1) return code;
	
	return Delete_handler(subjected, get);
}




int Btree::Internal_node_handler(Bnode ** subjected, Elem * deleted_elem)
{
	if((*subjected) == nullptr || deleted_elem == nullptr) throw(-1);

	Elem * get_node = nullptr;
	
	int code;
	
// Find inorder successor of deleted elem

	if(deleted_elem->next == nullptr) code = Find_node(&((*subjected)->upper_bound), get_node, true);
		
	else code = Find_node(&(deleted_elem->next->child), get_node, true); 

	if(code == -1) throw(-2);
	
	if(code == 1)
	{
		(*subjected)->Replace_node(deleted_elem, get_node);
		
		return 1;
	}

// Find inorder predecessor of deleted elem

	code = Find_node( &(deleted_elem->child), get_node, false);
	
	if(code == -1) throw(-3);

	(*subjected)->Replace_node(deleted_elem, get_node);

	if(code == 1) return 1;

// Rebalance btree	
	
	return Delete_handler(subjected, get_node);
}




int Btree::Delete_node(Bnode ** subjected, int key)
{
	if((*subjected) == nullptr) return -1;
	
	Elem * trv = (*subjected)->head;	

	while(trv != nullptr)
	{
	
// Traversing through list to search for any node having Key >= key

		if(trv->key == key)
		{
		
			if((*subjected)->leaf == 1)
			{
				(*subjected)->Delete_from_list(trv, true);
				
				if((*subjected)->num < (*subjected)->degree /2 + (*subjected)->degree %2 -1 && (*subjected)->root == 1)
				{
					if((*subjected)->num == 0)
					{
						delete (*subjected);
						
						(*subjected) = nullptr;
					}
					
					return 1;
				}
				
				if((*subjected)->num < (*subjected)->degree /2 + (*subjected)->degree %2 -1) return 0;
				
				return 1;
			}
			
			return Internal_node_handler(subjected, trv);
		}
		 
		
		if(trv->key > key)
		{
			int code = Delete_node(&(trv->child), key);
			
			if(code == 1 || code == -1) return code;
			
			return Delete_handler(subjected, trv);
		}
		
		trv = trv->next;
	}


// Inspect the last child in the node

	int code = Delete_node(&((*subjected)->upper_bound), key);
	
	if(code == 1 || code == -1) return code;

	return Delete_handler(subjected, nullptr);
}






bool Btree::Delete(int key)
{
	if(Delete_node(&root,key) == -1)
	{ 
		cout<<"key is not found\n";
		
		return false; 	
	}
	
	num--;

	cout<<"Deletion successfull\n";

	return true;
}






bool Btree::Insert(int key)
{
	if(root == nullptr)root = new Bnode(1,1,degree);
	
	bool exists = false;
	
	root->Insert(key,exists);
	
	num++;
	
	//cout<<endl;
	
	cout<<"Num is: "<<num<<endl;

	return exists;
}


int Btree::get_height(Bnode * ptr)
{
	
	if(ptr == nullptr) return 0;
	
	return 1 + get_height(ptr->upper_bound);
}


void Btree::Print_Bnode_FSM(Bnode * node)
{

	int indent = degree - node->num;
	
	int state = 0;
	
	int range = 2*degree - 1;
	
	Elem * traverse = node->head;
	
	if(traverse == nullptr)throw -1;
	
	for(int i = 0; i < range; i++)
	{
	
		switch(state)
		{
		//state '{'
			case 0:
			{
				cout<<"{";
			
				if(indent == 1)state = 2;
				
				else state = 1;
				
				break;
			}
		//state '_'1
			case 1:
			{
				cout<<" ";
				
				if(--indent == 1)state = 2;
				
				break;
			}
		//state '#'
			case 2:
			{
				cout<<traverse->key;
				
				traverse = traverse->next;
				
				if(traverse == nullptr)
				{
					if(i < (range - 2))state = 3;
					
					else state = 5;
					
					break;
				}
				
				state = 4;
				
				break;
			}
		//state '_'2
			case 3:
			{
				cout<<" ";
				
				if(i == range - 2)state = 5;
				
				break;
			}
		//state ','
			case 4:
			{
				cout<<",";
				
				state = 2;
				
				break;
			}
		//state '}'
			case 5:
			{
				cout<<"}";
				
				return;
			}
		//default
			default:return;		
		
		}
	
	}




}




void Btree::Print_Bnode(Bnode * node, int level, bool last_elem)
{
	if(level > 30){
	
		cout<<"Max height should be less than or equal to:"<<30<<endl;

		return;
	
	}
	
	int indent_length = pow(degree, level + 1) - degree;
	
	try { 
		Print_Bnode_FSM(node);
	}
	
	catch (int x ) {
	
      		cout << "Node is null\n";
   	}
   	
   	if(last_elem){
   		
   		cout<<"\n";
   		
   		return;
   	}
   	
   	for(int i = 0; i < indent_length; i++)cout<<" ";
}


void Btree::Print_Btree()
{

	if(root == nullptr)
	{
		cout<<"The tree is empty"<<endl;
		
		return;
	}

	Queue<Bnode> queue;
	
	int level = get_height(root);

	cout<<"Level is: "<<level<<endl;

	queue.Push(level, root,true);
	
	while(!queue.isEmpty())
	{
		Node<Bnode> * get = queue.Pop();
		
		Print_Bnode(get->node, get->level, get->endline);
		
		if(!get->node->leaf)
		{
			Elem * traverse = get->node->head;
			
			while(1)
			{
				queue.Push(get->level - 1,traverse->child);
				
				traverse = traverse->next;
				
				if(traverse == nullptr)
				{
					if(get->endline)queue.Push(get->level - 1,get->node->upper_bound,true);
					
					else queue.Push(get->level - 1,get->node->upper_bound);
					
					break;
				}
			}
		}
		
		delete get;
	}
}



