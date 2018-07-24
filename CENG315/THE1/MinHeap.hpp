#ifndef MINHEAP_HPP
#define MINHEAP_HPP

#include <iostream>
#include "MinHeapNode.hpp"


class MinHeap
{
	
public:
	/* Public Methods */
	MinHeap(); /* Default constructor */
	MinHeap(int capacity);
	~MinHeap(); /* Destructor */
	void swapMinHeapNode(MinHeapNode** first, MinHeapNode** second);
	void MinHeapify(int index);
	int isEmpty();
	MinHeapNode* extractMin();
	void decreaseKey(int vertex, int distance);
	bool inMinHeap(int v);


	/* Private Methods */

	int size;      // Number of heap nodes present currently
    int capacity;  // Capacity of min heap
    int *position;     // This is needed for decreaseKey()
    MinHeapNode **array;

private:
	



};

#endif