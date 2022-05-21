#pragma once

class WeightedGraph
{
	private:
		int** g;
		int nVertices;
	public:
	//returns the number of vertices
		int getNVertices();
	//returns weight of the edge connecting the given vertices
		int getWeight(char,char);
	// returns the indices of the neighbors of the vertex v as an int array
		int* returnNeighbors(int v);
	//returns the number of neighbors of the vertex v
		int numNeighbors(int v);
	// allocates the adjacency matrix & initializes edge weights from the specified file
		void loadGraphFromFile(ifstream&);
	// find the shortest path from the start vertex to all other vertices, by filling the prev array and the distances array
		void dijkstra(char startVertex, char* prev, Node distances[] );
};

//returns the number of vertices
int WeightedGraph::getNVertices()
{	
	/* code here */
}


//returns weight of the edge connecting the given vertices
int WeightedGraph::getWeight(char,char)
{	
	/* code here */
}


// returns the indices of the neighbors of the vertex v as an int array
int* WeightedGraph::returnNeighbors(int v)
{	
	/* code here */
}


//returns the number of neighbors of the vertex v
int WeightedGraph::numNeighbors(int v)
{	
	/* code here */
}


// allocates the adjacency matrix & initializes edge weights from the specified file
void WeightedGraph::loadGraphFromFile(ifstream&)
{	
	/* code here */
}


// find the shortest path from the start vertex to all other vertices, by filling the prev array and the distances array
void WeightedGraph::dijkstra(char startVertex, char* prev, Node distances[] )
{	
	/* code here */
}