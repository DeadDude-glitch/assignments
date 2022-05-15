#include "SLL.h"
#pragma once
// an implementaion of a queue using Single Linked List
// works by "first in first out" logic

template <class T>
class QueueSLL
{
private:
		SLL <T>* list;
public:
	// constructor
		QueueSLL () {list = new SLL <T>;}
		QueueSLL (SLL <T>  list) {this -> list = list;}
        QueueSLL (SLL <T>* list) {this -> list = list;}
	// utility
		void clear   ();
		bool isEmpty ();
		void enqueue (T value);
		T dequeue ();
		T front ();
	// getters
		SLL <T>& getList() {return list;}
};

template <class T>
void QueueSLL<T>::clear () 
{
	// clear the single linked list
		list -> SLL<T>::clear ();
}

template <class T>
void QueueSLL<T>::enqueue  (T value)
{
	// add to the tail of list a node with the parameter value
		list -> SLL<T>::addtoHead (value);
}

template <class T>
T QueueSLL<T>::dequeue ()
{
	// remove the head node from the SLL list
		return list -> SLL<T>::removeFromTail ();
}

template <class T>
bool QueueSLL<T>::isEmpty () {return list -> SLL<T>::isEmpty ();}

template <class T>
T QueueSLL<T>::front ()
{
	// return the value of list head node
		return list -> SLL<T>::getValueAtHead ();
}