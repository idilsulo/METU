#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>

#include "MinHeap.hpp"
#include "MinHeapNode.hpp"
#include "List.hpp"

class Graph
{
	
public:
	/* Public Methods */
	Graph(); /* Default constructor */
	~Graph(); /* Destructor */
	//Graph(int n);
	Graph(const std::string& inputFileName);
	void addEdge(int source, int destination, int weight);
	std::vector<int> Dijkstra(int source);

	void outputDestinations();

	void PrintGraphList();
	


	/* Private Methods */

	List* array;
	
	int n; /* Equal to n ? */
	int numberofDest; /* n - 2 - other cities */
	std::vector<int> warehouses;
	std::vector<int> destinations;

	std::vector< std::vector<int> > allSubsets;
	//int* dijkstra;

private:
	

};

#endif