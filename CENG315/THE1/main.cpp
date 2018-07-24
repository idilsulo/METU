#include "Graph.hpp"
#include "MinHeap.hpp"
#include "MinHeapNode.hpp"

#include "ListNode.hpp"
#include "List.hpp"

#include <iostream>
#include <string>

int main(int argv, char** argc)
{
	if(argv < 2)
	{
		return -1;
	}

	/*
	std::string line;
	line = "abc";

	std::cout << line[0] << std::endl;
	*/

	/*

	int w[1];

	w[0] = 1;

	int* y = w;
	std::cout << y[0] << std::endl;

	*/
	
	Graph newGraph(argc[1]);

	//std::cout << newGraph.array[0].head->weight << std::endl;
	
	//newGraph.PrintGraphList();


	//std::cout << std::endl;
/*
	for(int i=0; i<newGraph.n; i++){
		std::cout << newGraph.dijkstra[i] << std::endl;
	}
	*/

	newGraph.outputDestinations();
	
	return 0;
}
