#include <iostream>
#include "MinHeap.h"
#include "WeightedGraph.h"
using namespace std;

int main()
{
	// create graph from file 
		WeightedGraph wg;
		ifstream ifile("graph.txt");
		wg.loadGraphFromFile(ifile);
		ifile.close();
	// create array of vertcies labels
		char* p;
		p = new char[wg.getNVertices()];
	// create array of Nodes of graph 
		Node* n;
		n = new Node[wg.getNVertices()];
	// find the shortest path using dijkstra algorithm
		wg.dijkstra('g',p,n);
		cout<<endl<<"Node\tCost\tPrevious"; // print path syntax
	// print shortest path
		for(int i=0;i<wg.getNVertices();i++)
		{
			cout<<endl<<n[i].label<<"\t"<<n[i].cost<<"\t"<<p[i];
		}
		return 0;
}


/* 
this code was written by
	Ahmed Mamdouh 20205029	NCS1
	menna Shawkat ????????	??
*/