#pragma once
#include <iostream>
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

	struct edge {int weight; char v1_label; char v2_label;};	// read file edge-based input

// graded functions as requested from the assignment pdf file

	// returns the number of vertices
	int WeightedGraph::getNVertices () {return nVertices;}


	// returns weight of the edge connecting the given vertices
	int WeightedGraph::getWeight(char row, char col)
	{	
		int i = row - 97, j= col - 97;
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
				nEdges -= 1;
				try {
					// transform edge list into adj matrix
					// this step assumes that user names their vertcies according to the alphabitical order
					// if not a segementation error is to occur
					g[tolower(Edge.v1_label) - 97][tolower(Edge.v2_label) - 97] = Edge.weight;	// transform lower case characters into integers representation [0,25]
				}
				catch (const std::exception&) 
				{ 
					std::cout << "\n[INPUT FILE ERROR]\tdata types didn't match\n edge syntax: {vertix1_label} {vertix2_label} {weight_value}" << endl; 
					return; 
				}
			} 
			catch (const std::exception&)
			{
				std::cout << "\n[READING ERROR]\n most likely to be segementation";
				std::cout << "\nY = " << tolower(Edge.v1_label) - 97 << "\nX = " << tolower(Edge.v2_label) - 97 << endl;
			}
			
		}

	}
	
	/*
	* 
	// find the shortest path from the start vertex to all other vertices, by filling the prev array and the distances array
	void WeightedGraph::dijkstra (char startVertex, char* prev, Node distances[]) 
	{
		bool* sptSet = new bool [nVertices]; // sptSet[i] will be true if vertex i is included in shortest
		// path tree or shortest distance from src to i is finalized

		// Initialize all distances as INFINITE and stpSet[] as false
		for (int i = 0; i < nVertices; i++)
			distances[i] = INT_MAX, sptSet[i] = false;

		// Distance of source vertex from itself is always 0
		distances[src] = 0;

		// Find shortest path for all vertices
		for (int count = 0; count < nVertices - 1; count++) {
			// Pick the minimum distance vertex from the set of vertices not
			// yet processed. u is always equal to src in the first iteration.
			int u = minDistance (distances, sptSet);

			// Mark the picked vertex as processed
			sptSet[u] = true;

			// Update dist value of the adjacent vertices of the picked vertex.
			for (int v = 0; v < nVertices; v++)

				// Update dist[v] only if is not in sptSet, there is an edge from
				// u to v, and total weight of path from src to  v through u is
				// smaller than current value of dist[v]
				if (!sptSet[v] && g[u][v] && distances[u].cost != INT_MAX
					&& distances[u].cost + g[u][v] < distances[v].cost)
					distances[v].cost = distances[u].cost + g[u][v];
		}
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