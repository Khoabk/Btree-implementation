#ifndef QUEUE_H
#define QUEUE_H


class Btree;

template<class T> class Queue;



template<class T>
class Node
{
	int level;
	
	bool endline;
	
	T * node;
	
	Node * next;
	
	friend class Queue<T>;
	
	friend class Btree;
	
	public:
	
	Node(int level = 0,bool endline = false, T * node = nullptr, Node * next = nullptr):level(level), endline(endline), node(node), next(next){}
	
	~Node(){ delete next; }
};





template<class T> class Queue
{
	Node<T> * head;
	
	Node<T> * tail;
	
	public:
	
	Queue():head(nullptr), tail(nullptr){}
	
	~Queue(){ delete head; }
	
	bool isEmpty(){ return (head == nullptr);}
	
	void Push(int level, T * node, bool endline = false);
	
	Node<T> * Pop();
};




#endif
