#include <cstddef>
#pragma once
// decleration of a node that has value and a pointer to another node
template<class T> class Node
{
private:
		Node* next; 
		T     info;
public: 
	// constructors
		Node (T value, Node* n=NULL) {next = n; info = value;} 
	// getters
		Node* getNext () {return next;}
		T     getInfo () {return info;} 
	// setters
		void  setNext (Node* pointer) {next = pointer;}
		void  setInfo (T     value  ) {info = value;}; 
};
