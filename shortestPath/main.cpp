#include <iostream>
#include "Structures.h"
#include "MinHeap.h"
#include "WeightedGraph.h"
using namespace std;

const string filePath = "graph.txt";

int main()
{
	// create graph from file 
	cout << "[~] creating graph from file\n";
	WeightedGraph graph;
	fstream ifile(filePath, std::ios::in);
	graph.loadGraphFromFile(ifile);
	ifile.close();
	
	// create array of vertcies labels
	cout << "[~] extracting labels\n";
	char* label;
	label = new char [graph.getNVertices()];
	
	// create array of Nodes of graph
	cout << "[~] Creating Path Nodes\n";
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
*/