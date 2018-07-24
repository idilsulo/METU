#ifndef MINHEAPNODE_HPP
#define MINHEAPNODE_HPP

#include <iostream>


class MinHeapNode
{
	
public:
	/* Public Methods */
	MinHeapNode(); /* Default constructor */
	MinHeapNode(int vertex, int distance);
	~MinHeapNode(); /* Destructor */	
	void PrintNode();

	/* Private Methods */

	int vertex;
	int distance;

private:
	

};

#endif