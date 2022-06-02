#include <iostream>
#include <fstream>
#include "MinHeap.h"
#include "Structures.h"
#pragma once
using namespace std;

// representation of a weighted directed graph using 2D array as a vertices adjacency matrix
// such that if vertex 0 and vertex 2 are adjacent then g[0][2] = g[2][0] = the edge Weight
// which guarantees the matrix symmetric property

class WeightedGraph
{
	private:
			int** g;
			int nVertices;
	public:
		// constructors and deconstructors
			WeightedGraph()													// create an empty weighted graph
			{
				// nullify pointers
				nVertices = 0;
				g = NULL;
			}

			WeightedGraph(const int size, int default_value = 0)			// create a weighted graph full default value 
			{
					nVertices = size;
				// create NxN matrix
					g = new int* [size];									// an N size array of int pointer
					for (int i=0; i<size; i++)
					{
						g[i] = new int[size];								// an N size array of int variables
						for (int j = 0; j < size; j++)
							{g[i][j] = default_value;}						// filled with default value		
						
					}
			}

			~WeightedGraph() { delete[] g; }								// deconstruct obj
	
		// requested funtions (definition cannot be editied)
			int getNVertices();												// returns the number of vertices
			int getWeight (char,char);										// returns weight of the edge connecting the given vertices
			int numNeighbors (int v);										// returns the number of neighbors of the vertex v
			int* returnNeighbors (int v);									// returns the indices of the neighbors of the vertex v as an int array
			void loadGraphFromFile (fstream& file);							// allocates the adjacency matrix & initializes edge weights from the specified file
			void dijkstra (char src, char label[], Node dist[]);	// find the shortest path from the start vertex to all other vertices, by filling the prev array and the distances array
	
		// utility functions (non-graded nor requested)
			bool isNeighbor (int v1, int v2);								// if g[v1][v2] > 0 then true  
			int minDistance(Node dist[], bool sptSet[]);

		// friend classes
			friend class MinHeap;
};




/////////////////////////////////////////////////////////////////
// non graded functions/structures for simplyification of code
///////////////////////////////////////////////////////////////
	


	// if exist v1 --> v2 or v2 --> v1 return true else false
	bool WeightedGraph::isNeighbor(int v1, int v2) { return (WeightedGraph::g[v1][v2] > 0 || WeightedGraph::g[v2][v1] > 0); }

	int WeightedGraph::minDistance(Node dist[], bool sptSet[])
	{
		// Initialize min value
		int min = INT_MAX;
		int min_index;
		for (int i = 0; i < nVertices; i++)
			if (sptSet[i] == false && dist[i].cost <= min)
				min = dist[i].cost, min_index = i;
		return min_index;
	}






///////////////////////////////////////////////////////////////////////////
// graded functions as requested from the assignment pdf file
/////////////////////////////////////////////////////////////////////////

	// returns the number of vertices
	int WeightedGraph::getNVertices () { return nVertices; }	

	// returns weight of the edge connecting the given vertices
	int WeightedGraph::getWeight(char row, char col) { return g[row - 97][col - 97]; }

	// returns the indices of the neighbors of the vertex v as an int array
	int* WeightedGraph::returnNeighbors (int v)
	{	
		// create array of neighbors
		int* neighbors = new int [nVertices];
		// travese row till it end
		for (int n = 0,i = 0; n < nVertices; n++) 
		{
			// add vertix to neighbors
			if (isNeighbor(v, n)) { neighbors[i] = g[v][n]; }
		}
		return neighbors;
	}


	// returns the number of neighbors of the vertex v
	int WeightedGraph::numNeighbors (int v)
	{	
		int count = 0;
		// traverse vertex's row
		for (int i = 0; i < WeightedGraph::nVertices; i++) 
		{
			if (WeightedGraph::g[v][i] > 0 && v != i) { count++; }			// count values greater than 1 (dont count self)
		}
		return count;
	}


	// allocates the adjacency matrix & initializes edge weights from the specified file
	void WeightedGraph::loadGraphFromFile(fstream& file)
	{
		int nEdges = 0;
		file >> nVertices;
		file >> nEdges;
		edge Edge;
		// read edges and import them into adj matrix
		while (nEdges > 0)
		{

			file >> Edge.v1_label;
			file >> Edge.v2_label;
			file >> Edge.weight;
			// checks if characters are alphabitc
			if ((Edge.v1_label - 97) < 0 || (Edge.v2_label - 97) < 0) throw false;
			nEdges--;
		}
	}
	
	



	void WeightedGraph::dijkstra(char src, char label[], Node dist[])
	{
		// src index
		int srcIndex = tolower(src) - 97;
		// sptSet[i] will true if vertex i is included
		bool* sptSet = new bool [nVertices];

		// Parent array to store shortest path tree
		Node* parent = new Node [nVertices];

		// Initialize all distances as INFINITE
		for (int i = 0; i < nVertices; i++) dist[i].label = label[i];
			

		// Distance to vertex from itself is always 0
		dist[src-97].cost = 0;

		MinHeap heap (nVertices);
		heap.buildMinHeap(dist, nVertices);
		
		
		// Find shortest path for all vertices
		for (int count = 0; count < nVertices - 1; count++) {
			// Pick the minimum distance vertex 
			int u = minDistance(dist, sptSet);
			// Mark the picked vertex as processed
			sptSet[u] = true;
			// Update dist value of the adjacent vertices of the
			// picked vertex.
			for (int v = 0; v < nVertices; v++)
				// Update dist[v] only if is not in sptSet,
				// there is an edge from u to v, and total
				// weight of path from src to v through u is
				// smaller than current value of dist[v]
				if (!sptSet[v] && g[u][v] && dist[u].cost + g[u][v] < dist[v].cost) 
				{
					parent[v].cost = u;
					dist[v].cost = dist[u].cost + g[u][v];
				}
		}
	}





	
	/*
	// find the shortest path from the start vertex to all other vertices, by filling the prev array and the distances array
	// calculates distances of shortest paths from src to all vertices. It is a O(ELogV) function
	void WeightedGraph::dijkstra (char startVertex, char* prev, Node distances[]) 
	{
		// setting up variables for algorithm
		startVertex = tolower(startVertex);
		const int vertex = startVertex - 97;	// get start vertex index on the adj matrix
		Node* path = new Node[nVertices];
		char* prev = new char[nVertices];
		// vist unvisited vertex with smallest cost
		// for i in current vertix nigbours set cost = current cost + edge cost
		for (int i = 0; i < nVertices; i++)
		{
			// create neighbors heap
			int* neighborsIndex = returnNeighbors(i);
			prev[i] = neighborsIndex[i]+97;
			MinHeap* neighbors = new MinHeap (numNeighbors(i));
			neighbors[i].decreaseKey( prev[i], g [vertex] [neighborsIndex[i]] + g[vertex][i]);
		}

		// calculate distance of each neighbour from vertex
		// update shortest path
		// mark current vertix visited
	}

	
	// find the shortest path from the start vertex to all other vertices
	// calculates distances of shortest paths from src to all vertices.
	void WeightedGraph::dijkstra (char startVertex, char* prev, Node distances[])
	{
		// dist values used to pick minimum weight edge in cut
		int* distance = new int [nVertices];
		// minHeap represents set E
		MinHeap* minHeap = new MinHeap(nVertices);
		// Initialize min heap with all
		// vertices. dist value of all vertices
		for (int v = 0; v < nVertices; ++v)
		{
			Node* tmp = new Node(v+97, distances[v].cost);
			distances[v].cost = INT_MAX;
			minHeap[v] = tmp;
		}
		// Make dist value of src vertex
		// as 0 so that it is extracted first
		minHeap[startVertex] = new Node(startVertex, distances[startVertex].cost);
		distances[startVertex].cost = 0;
		minHeap->decreaseKey( startVertex, distances[startVertex].cost);
		// In the followin loop,
		// min heap contains all nodes
		// whose shortest distance
		// is not yet finalized.
		Node minHeapNode;
		while (!minHeap->isEmpty())
		{
			// Extract the vertex with the minimum distance 
			// Store the extracted vertex number
			minHeapNode = minHeap->extractMin();
			int u = minHeapNode.cost;
			// Traverse through all adjacent vertices of the extracted
			// vertex and update their distance values
			struct AdjListNode* pCrawl = g[u].head;
			while (pCrawl != NULL)
			{
				int v = pCrawl->dest;
				// If shortest distance to v is
				// not finalized yet, and distance to v
				// through u is less than its
				// previously calculated distance
				if (minHeap->inHeap(v) && distance[u] != INT_MAX && pCrawl->weight + distance[u].cost < distance[v].cost)
				{
					distances[v] = distances[u] + pCrawl->weight;
					// update distance value in min heap also
					minHeap->decreaseKey( v, distances[v].cost);
				}
				pCrawl = pCrawl->next;
			}
		}
	}



/*

* this is the shape of the adj matrix 
* only writeen for comprehension
	   
	x| A B C D E
	-+--+-+-+-+------
	A| 0 0 0 0 0 ....
	B| 0 0 0 0 0 ....
	C| 0 0 0 0 0 ....
	D| 0 0 0 0 0 ....
	E| 0 0 0 0 0 ....
	.| . . . . . 
	.| . . . . . 

*/


/*

The file graph.txt will have the following format:

	nVertices
	number-of-edges			# let it be n
	vertix1 vertix2 weight	#1
	vertix1 vertix2 weight	#2
	vertix1 vertix2 weight	#3
	vertix1 vertix2 weight	#4
	....... ....... ......  ..
	....... ....... ......  ..
	....... ....... ......  #n

*/