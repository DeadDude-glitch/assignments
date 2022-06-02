#include "Structures.h"
#include <iostream>
#pragma once

class MinHeap
{
	private:
		Node* heap;										// an array of nodes
		int _size;										// size of array
	public:
		// constructors
		MinHeap(int size){
			_size = size;
			heap = new Node [_size];
			while (size >= 0) { heap[size--].cost = INT_MAX; }
		}

		MinHeap(){			// default constructor
			_size = 0;
			heap = NULL;
		}

		// requested functions
		Node extractMin	  ();							// returns & removes the node with minimum cost
		void buildMinHeap ( Node* arr, int size );			// allocates array then builds a min-heap from an array of struct Node with the given size
		void minHeapify ( int index );					// restores the min-heap property for the “heap” array using the given index	
		void decreaseKey ( char label, int newCost );	// decreases the node that has the given label to newCost
		int	 parent	( int i );							// returns the index of the parent of i by index
		bool inHeap ( char c );							// checks if the node with the given label is in the heap
		int	 getSize ();								// returns size of the heap (just a getter)
		
		// not requested functions (not graded)
		int  left_child  (int i);
		int  right_child (int i);
		void minHeapify ();								// minHeapify the entire tree
		int  parent (char c);							// returns the index of the parent of c by label
		bool isEmpty ();								// checks if heap is empty
		__int64 getAllocationSize();					// get the allocation size
		void increaseKey(char label, int newCost);
		Node operator [](int index) { return heap[index]; }
		Node operator [](char label) { return heap[label-97]; }
};




////////////////////////////
// none graded functios
//////////////////////////
int  MinHeap::left_child (int i) { return i * 2 + 1; }			// Left Child Index  = nodeIndex * 2 + 1
int  MinHeap::right_child(int i) { return i * 2 + 2; }			// Right Child Index  = nodeIndex * 2 + 2
bool MinHeap::isEmpty() { return this->_size == 0; }
void MinHeap::minHeapify() { minHeapify(0); }
// returns array size of the heap
__int64 MinHeap::getAllocationSize()
{	
	// pointer calculation to find array size
	// heap points to the first element									heap --> [1, 2, 3][ ,  ,  ]
	// *(&heap+1) points to {_size} elements ahead of heap						 ^		  ^
	// heap end byte - heap first byte = size									heap     *(&heap+1)
	return *(&heap + 1) - heap;	
}



////////////////////////////
// graded functios
//////////////////////////

// returns & removes the node with minimum cost
Node MinHeap::extractMin()
{	
	// save root node into variable
	Node root = heap[0];
	// set root node to last node 
	heap[0] = heap[--_size];
	// TODO: delete last node
	minHeapify(0);									// and SEGMENTATION ERROR might occure here
	return root;
}

// allocates array then builds a min-heap from an array of struct Node with the given size
void MinHeap::buildMinHeap (Node* arr, int size)
{	
	heap = arr;
	minHeapify();
}
	
// restores the min-heap property for the “heap” array using the given index and size n
void MinHeap::minHeapify (int index)
{	
	// find smallest value
	int smallest = index;
	if (left_child(index) < _size && heap[left_child(index)].cost < heap[index].cost)
		smallest = left_child(index);
	if (right_child(index) < _size && heap[right_child(index)].cost < heap[smallest].cost)
		smallest = right_child(index);
	// if edit is required
	if (smallest != index)
	{
		Switch(heap[index].cost, heap[smallest].cost);
		minHeapify(smallest);
	}
}
	
// decreases the node that has the given label to newCost
void MinHeap::decreaseKey (char label,int newCost)
{
	try {
		if (label - 97 < 0) throw 0;
		for (int i = 0; i < _size; i++) if (label == heap[i].label) heap[i].cost -= newCost;
	}
	catch (int) { std::cout << "\n[WARNING] non-alphabitic label is invalid\n"; }
	minHeapify();
}

// increase the node that has the given label to newcost
void MinHeap::increaseKey(char label, int newCost)
{
	try {
		if (label - 97 < 0) throw 0;
		for (int i = 0; i < _size; i++) if (label == heap[i].label) heap[i].cost += newCost;
	}
	catch (int) { std::cout << "\n[WARNING] non-alphabitic label is invalid\n"; }
	minHeapify();
}

// returns the index of the parent of i
int MinHeap::parent (int  i) { return (i -  1) / 2; }
int MinHeap::parent (char c) { return (c - 98) / 2; }	// by label

// returns current size of the heap
int MinHeap::getSize()
{	// pointer calculation to find array size
	// heap points to the first element									heap --> [1, 2, 3][ ,  ,  ]
	// *(&heap+1) points to {_size} elements ahead of heap						 ^		  ^
	// (heap first byte - heap last byte) / datatype byte size = size			heap     *(&heap+1)
	// return  *(&heap + 1) - heap;
	return _size;
}

// checks if the node with the given label is in the heap
bool MinHeap::inHeap (char label)
{	
	try {
		if (label - 97 < 0) throw false;	// checks if alphabitic 
		// traverse the node array
		for (int i = 0; i < _size; i++)
			// return true if a Node is found with same label
			if (heap[i].isDefined() && label == heap[i].label) return true; 
		return false;
	}catch (bool) { std::cout << "\n[ERROR] labels must be alphabitic\n"; }
}

/*
Heap Structure
	 __________
	|node array|
	--------------------------------------------------------------------------------------------------------------------------->
	|	[0]				|	[1]				|	[2]				|	[3]				|	[4]				|	[5]				
	|	<label|cost>	|	<label|cost>	|	<label|cost>	|	<label|cost>	|	<label|cost>	|	<label|cost>	
	--------------------------------------------------------------------------------------------------------------------------->

	Parent Node Index  = (nodeIndex - 1) /2				[		 0         ]
	Left   Child Index  = nodeIndex * 2 + 1 			[	1	 ][   2    ]
	Right  Child Index  = nodeIndex * 2 + 2 		    [ 3 ][ 4 ][ 5 ][ 6 ]
*/
