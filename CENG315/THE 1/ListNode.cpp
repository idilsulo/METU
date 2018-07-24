#include "ListNode.hpp"

ListNode::ListNode(){
	this->next = NULL;
}


ListNode::ListNode(int destination, int weight){
	
	this->destination = destination;
	this->weight = weight;
	this->next = NULL;

}


ListNode::~ListNode(){

	
}