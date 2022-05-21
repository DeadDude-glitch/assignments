#pragma once

struct Node
{
	char label;
	int cost;
};

class MinHeap
{
	private:
		Node* heap; //an array of nodes
		int _size; //size of array
	public:
		
		Node extractMin ();								// returns & removes the node with minimum cost
		void buildMinHeap (Node[], int);				// allocates array then builds a min-heap from an array of struct Node with the given size
		void minHeapify   (int i, int n);				// restores the min-heap property for the “heap” array using the given index and size n
		void decreaseKey  (char label, int newCost);	// decreases the node that has the given label to newCost
		int	 parent (int  i);							// returns the index of the parent of i
		bool inHeap (char c);							// checks if the node with the given label is in the heap
		int	 getSize ();								// returns size of the heap
};

// returns & removes the node with minimum cost
Node MinHeap::extractMin()
{	
	/* code here*/
}

// allocates array then builds a min-heap from an array of struct Node with the given size
void MinHeap::buildMinHeap (Node[],int)
{	
	/* code here*/
}
	
// restores the min-heap property for the “heap” array using the given index and size n
void MinHeap::minHeapify (int i, int n)
{	
	/* code here*/
}
	
// decreases the node that has the given label to newCost
void MinHeap::decreaseKey (char label,int newCost)
{	
	/* code here*/
}

// returns the index of the parent of i
int MinHeap::parent (int i)
{	
	/* code here*/
}

// returns size of the heap
int MinHeap::getSize()
{	
	/* code here*/
}

// checks if the node with the given label is in the heap
bool MinHeap::inHeap (char)
{	
	/* code here*/
}