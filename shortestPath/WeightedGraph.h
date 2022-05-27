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
			void dijkstra (char startVertex, char* prev, Node distances[] );// find the shortest path from the start vertex to all other vertices, by filling the prev array and the distances array
	
		// utility functions (non-graded nor requested)
			void addEdge (char v1, char v2, int weight);					// add edge between v1 and v2
			void addEdge (int  v1, int  v2, int weight);					// add edge between v1 and v2
			void removeEdge (int  v1, int  v2);								// remove edge between v1 and v2
			void removeEdge (char v1, char v2);								// remove edge between v1 and v2
			bool isNeighbor (int v1, int v2);								// if g[v1][v2] > 0 then true  
};




/////////////////////////////////////////////////////////////////
// non graded functions/structures for simplyification of code
///////////////////////////////////////////////////////////////
	
	// add edge between v1 and v2
	void WeightedGraph::addEdge (int  v1, int  v2, int weight) { g[v1][v2] = weight; }
	void WeightedGraph::addEdge (char v1, char v2, int weight) { g[v1 - 97][v2 - 97] = weight; }

	// removes edge between v1 and v2
	void WeightedGraph::removeEdge (int  v1, int  v2) { WeightedGraph::g[v1] [v2] = 0; }
	void WeightedGraph::removeEdge (char v1, char v2) { WeightedGraph::g[v1-97][v2-97] = 0; }

	// if exist v1 --> v2 or v2 --> v1 return true else false
	bool WeightedGraph::isNeighbor(int v1, int v2) { return (WeightedGraph::g[v1][v2] > 0 || WeightedGraph::g[v2][v1] > 0); }



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
			try{
				file >> Edge.v1_label;
				file >> Edge.v2_label;
				file >> Edge.weight;
				// checks if characters are alphabitc
				if (Edge.v1_label - 97 < 0 || Edge.v2_label - 97 < 0) throw false;
				nEdges -= 1;
				try {
					// transform edge list into adj matrix
					// this step assumes that user names vertcies according to the alphabitical order
					// if not a segementation error is to occur
					g[tolower(Edge.v1_label) - 97][tolower(Edge.v2_label) - 97] = Edge.weight;	// transform lower case characters into integers representation [0,25]
				}
				catch (const std::exception&) 
				{ 
					std::cout << "\n[INPUT FILE ERROR]\tdata types didn't match\n EDGE SYNTAX: {vertix1_label} {vertix2_label} {weight_value}" << endl; 
					return; 
				}
			} 
			catch (const std::exception&)
			{
				std::cout << "\n[READING ERROR]\n most likely to be segementation";
				std::cout << "\n[INPUT FILE ERROR]\tdata types didn't match\n EDGE  SYNTAX: {vertix1_label} {vertix2_label} {weight_value}" << endl;
				std::cout << "\nY = " << tolower(Edge.v1_label) - 97 << "\nX = " << tolower(Edge.v2_label) - 97 << endl;
			}
			catch (bool) { std::cout << "\n[INPUT FILE ERROR]\tdata types didn't match"
									 << "\n EDGE  SYNTAX : {char v1} {char v2} {integer weight}" << endl; }
			
		}
	}
	
	/*
	// find the shortest path from the start vertex to all other vertices, by filling the prev array and the distances array
	// calculates distances of shortest paths from src to all vertices. It is a O(ELogV) function
	void WeightedGraph::dijkstra (char startVertex, char* prev, Node distances[]) 
	{
		// dist values used to pick minimum weight edge in cut
		int* distance = new int [nVertices];

		// minHeap represents set E
		struct MinHeap* minHeap = createMinHeap(V);

		// Initialize min heap with all 
		// vertices. dist value of all vertices 
		for (int v = 0; v < V; ++v)
		{
			dist[v] = INT_MAX;
			minHeap->array[v] = newMinHeapNode(v, dist[v]);
			minHeap->pos[v] = v;
		}

		// Make dist value of src vertex 
		// as 0 so that it is extracted first
		minHeap->array[src] = newMinHeapNode(src, dist[src]);
		minHeap->pos[src] = src;
		dist[src] = 0;
		decreaseKey(minHeap, src, dist[src]);

		// Initially size of min heap is equal to V
		minHeap->size = V;

		// In the followin loop, 
		// min heap contains all nodes
		// whose shortest distance 
		// is not yet finalized.
		while (!isEmpty(minHeap))
		{
			// Extract the vertex with 
			// minimum distance value
			struct MinHeapNode* minHeapNode = extractMin(minHeap);

			// Store the extracted vertex number
			int u = minHeapNode->v;

			// Traverse through all adjacent 
			// vertices of u (the extracted
			// vertex) and update 
			// their distance values
			struct AdjListNode* pCrawl = graph->array[u].head;
			while (pCrawl != NULL)
			{
				int v = pCrawl->dest;
				// If shortest distance to v is
				// not finalized yet, and distance to v
				// through u is less than its 
				// previously calculated distance
				if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && pCrawl->weight + dist[u] < dist[v])
				{
					dist[v] = dist[u] + pCrawl->weight;
					// update distance 
					// value in min heap also
					decreaseKey(minHeap, v, dist[v]);
				}
				pCrawl = pCrawl->next;
			}
		}
		// print the calculated shortest distances
		printArr(dist, V);
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