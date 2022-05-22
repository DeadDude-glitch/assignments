#pragma once
#include <fstream>
#include "MinHeap.h"	// only to define struct of node
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
						g[i] = new int[size];				// an N size array of int variables
						for (int j = 0; j < size; j++)
							{g[i][j] = default_value;}		// filled with default value		
						
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
			bool addEdge (int v1, int v2, int weight);						// add edge between v1 and v2
			void removeEdge (int v1, int v2);								// remove edge between v1 and v2
			bool isNeighbor (int v1, int v2);								// if g[v1][v2] > 0 then true  
};





// non graded functions/structures for simplyification of code
	bool WeightedGraph::addEdge(int v1, int v2, int weight)				// add edge between v1 and v2
	{
		// if edge already exists return false
		if (WeightedGraph::g[v1][v2] != 0 || WeightedGraph::g[v2][v1] != 0)
			{return false;}
		
		WeightedGraph::g[v1][v2] = weight;
		return true;
		
	}

	void WeightedGraph::removeEdge(int v1, int v2)						// add edge between v1 and v2
	{
		WeightedGraph::g[v1][v2] = 0;
		WeightedGraph::g[v2][v1] = 0;
	}

	bool WeightedGraph::isNeighbor(int v1, int v2)						// if g[v1][v2] > 0 then true
	{																	// else return false
		if (WeightedGraph::g [v1][v2] > 0 || WeightedGraph::g [v2][v1] > 0)
			{ return true; }
		else 
			return false;
	}

	struct edge {int weight; char v1; char v2;};	// read file edge-based input

// graded functions as requested from the assignment pdf file

	// returns the number of vertices
	int WeightedGraph::getNVertices () {return nVertices;}


	// returns weight of the edge connecting the given vertices
	int WeightedGraph::getWeight(char row, char col)
	{	
		int i=0, j=0;
		// TODO: find i and j from parameters
		return std::max (g[i][j], g[j][i]);
	}


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
			if (WeightedGraph::g[v][i] > 0 && v != i) { count++; }			// count values greater than 1
		}
		return count;
	}


	// allocates the adjacency matrix & initializes edge weights from the specified file
	void WeightedGraph::loadGraphFromFile(fstream& file)
	{
		int nEdges;
		file >> nVertices;
		file >> nEdges;
		edge* e = new edge[(nVertices * (nVertices - 1))];   // max number of edges (complete graph)
		while (nEdges > 0)
		{
			file >> e[nEdges].v1;
			file >> e[nEdges].v2;
			file >> e[nEdges].weight;
			nEdges--;
		}
	}

	// find the shortest path from the start vertex to all other vertices, by filling the prev array and the distances array
	void WeightedGraph::dijkstra (char startVertex, char* prev, Node distances[]) 
	{ 
		/* code here */
		return;
	}






/*

* this is the shape of the adj matrix 
* only writeen for comprehension


			0|1|2|3|4|....N
                   
		0|  0 0 0 0 0 ....
		1|  0 0 0 0 0 ....
		2|  0 0 0 0 0 ....
		3|  0 0 0 0 0 ....
		4|  0 0 0 0 0 ....
		.   . . . . .
		.   . . . . .
		.   . . . . .
		N



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
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
 >>>>>>>>>> Example File:
///////////////////////////////////
line 00| 8
line 01| 15
line 02| g a 9
line 03| g e 14
line 04| g f 15
line 05| a b 24
line 06| b d 2
line 07| b h 19
line 08| c b 6
line 09| c h 6
line 10| d c 11
line 11| d h 16
line 12| e b 18
line 13| e d 30
line 14| e f 5
line 15| f d 20
line 16| f h 44
////////////////////////////////////
<<<<<<<<<<<<<<< reading algo
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
struct edge {int weight, char v1, char v2}
file >> nVertices
file >> loopTimes
edge* e = new edge[(nVertices*(nVertices-1))/2];   // max number of edges (complete graph)
while (loopTimes>0)
{
	file >> e[loopTimes].v1;
	file >> e[loopTimes].v2;
	file >> e[loopTimes].weight;
}
*/