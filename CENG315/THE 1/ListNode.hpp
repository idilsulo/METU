#ifndef LISTNODE_HPP
#define LISTNODE_HPP

#include <iostream>

#include "MinHeap.hpp"

class ListNode
{
	
public:
	/* Public Methods */
	ListNode(); /* Default constructor */
	ListNode(int destination, int weight);
	~ListNode(); /* Destructor */


	/* Private Methods */

	/* Definiton of a node in adjacency list */
	int destination;
	int weight;
	ListNode* next;

private:
	


};

#endif