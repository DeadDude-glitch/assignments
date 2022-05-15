#include "SLL.h"
#pragma once
// an implementaion of a stack using Single Linked List
// works by "first in last out" logic

template <class T>
class StackSLL
{
private:
		SLL <T>* list;
public:
	// constructor
		StackSLL () {list = new SLL <T>;}
		StackSLL (SLL <T> list) {this -> list = list;}
	// utility
		void clear ();
		void push  (T value);
		bool isEmpty ();
		T pop ();
		T top ();
	// getters
		SLL <T>* getList() {return list;}
};

template <class T>
void StackSLL<T>::clear () 
{
	// clear the single linked list
		list -> SLL<T>::clear ();
}

template <class T>
void StackSLL<T>::push  (T value)
{
	// add to the head of list a node with the parameter value
		list -> SLL<T>::addtoHead (value);
}

template <class T>
T StackSLL<T>::pop ()
{
	// remove the head node from the SLL list
		return list -> SLL<T>::removeFromHead ();
}

template <class T>
bool StackSLL<T>::isEmpty () {return list -> SLL<T>::isEmpty ();}

template <class T>
T StackSLL<T>::top ()
{
	// return the value of list head node
		return list -> SLL<T>::getValueAtHead();
}
