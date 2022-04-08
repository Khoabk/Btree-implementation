#include "Queue.h"
#include <iostream>


using namespace std;

template <class T>
void Queue<T>::Push(int level, T * node, bool endline)
{
	if(node == nullptr)
	{
		cout<<"node is empty"<<endl;
		
		return;
	}

	//If queue is empty
	if(head == nullptr)
	{
		head = new Node<T>(level,endline,node);
		
		tail = head;
		
		return;
	}
	
	//Queue is not empty
	tail->next = new Node<T>(level,endline,node);
	
	tail = tail->next;	
}


template <class T>
Node<T>* Queue<T>::Pop()
{
	//If queue is empty return null
	if(head == nullptr)return nullptr;
	
	//If queue is not empty return the first element
	Node<T> * get = head;
	
	head = head->next;
	
	get->next = nullptr;
	
	return get;
}
