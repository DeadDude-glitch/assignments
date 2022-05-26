#include <iostream>
#include "MinHeap.h"
#include "WeightedGraph.h"
using namespace std;

const string fileName = "graph.txt";

int main()
{
	// create graph from file 
	WeightedGraph graph;
	fstream ifile(fileName, std::ios::in);
	graph.loadGraphFromFile(ifile);
	ifile.close();
	// create array of vertcies labels
	char* label;
	label = new char [graph.getNVertices()];
	// create array of Nodes of graph 
	Node* n;
	n = new Node [graph.getNVertices()];
	// find the shortest path using dijkstra algorithm
	graph.dijkstra ('g', label, n);
	cout << endl << "Node\tCost\tPrevious"; // print path syntax
	// print shortest path
	for (int i = 0; i < graph.getNVertices(); i++)
	{
		cout << endl << n[i].label << "\t" << n[i].cost << "\t" << label[i];
	}
	return 0;
}


/*
this code was written by
	Ahmed Mamdouh 20205029	NCS1
	Menna Shawkat ????????	??
*/