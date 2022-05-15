#include "Node.h"
#include <iostream>
using namespace std;
#pragma once
// decleartion of single linked list object with a head and tail pointers using Node class

template <class T>
class SLL 
{ 
private:
		Node <T> *head;
		Node <T> *tail;
public: 
	// constructors
		SLL () {head = tail = NULL;}
	// utility functions
		void addtoHead (T);
		void addtoTail (T);
		T removeFromHead ();
		T removeFromTail ();
		T getValueAtHead (); // returns the value at head without deleting it
		bool isEmpty();
		void clear(); 
		void print();
	// operator overloading functions
		friend ostream& operator << (iostream& output, const SLL <T> & obj)
		{
			// while there is a next node print the current element info
				Node <T>* current = obj.head;
				while (current != NULL){
					output << current -> getInfo() << " ";
					current = current->getNext();
				}
				return output;
		}
};

// simple requested functions 
template <class T>
T SLL<T>::getValueAtHead () {return SLL<T>::head -> getInfo ();}
template <class T>
bool SLL<T>::isEmpty  () {return SLL<T>::head == NULL && SLL<T>::tail == NULL;}

// adding functions
template <class T>
void SLL<T>::addtoHead (T value){
	// construct new node points to the head node
		Node <T>* newNode = new Node<T> (value, head);
	// redefine the new node as head
		head = newNode;
}

template <class T>
void SLL<T>::addtoTail (T value){
	// construct new node
		Node <T>* newNode = new Node<T> (value, NULL);
	// make tail points to the new node
		tail -> setNext (newNode);
	// redefine the new node as tail
		tail = newNode;
}

// removing functions
template <class T>
void SLL<T>::clear (){
	while ( ! isEmpty() )
	{
		removeFromHead();
		if (SLL<T>::tail != NULL) {SLL<T>::removeFromTail();} // just making sure every node is deleted
	}
}

template <class T>
T SLL<T>::removeFromHead () {
	// locate the head memory location
		Node <T>* previous = SLL<T>::head;
		T value = head -> getInfo ();
	// move the head to the next node
		head = head -> getNext();
	// delete the previous head node
		delete previous;
	// return the removed value
		return value;
}
template <class T>
T SLL<T>::removeFromTail () {
	// locate the tail memory location
		Node <T>* current = SLL<T>::head;
		T value = SLL<T>::tail -> getInfo ();
	// traverse the list to the tail predecessor
		while (current -> getNext () != SLL<T>::tail) {current = current -> getNext ();}
	// relocate tail to the previous node
		SLL<T>::tail = current;
		current = current -> getNext();
		delete current;
		SLL<T>::tail -> setNext (NULL);
	// return the removed value
		return  value;
}