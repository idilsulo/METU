#include "MinHeapNode.hpp"

#include <iostream>

MinHeapNode::MinHeapNode(){

}

MinHeapNode::MinHeapNode(int vertex, int distance){
	this->vertex = vertex;
	this->distance = distance;
}

MinHeapNode::~MinHeapNode(){

}

void MinHeapNode::PrintNode(){

	std::cout << "Contents of the node:" << std::endl;
	std::cout << this->vertex << std::endl;
	std::cout << this->distance << std::endl;
}