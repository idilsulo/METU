#include "MinHeap.hpp"


MinHeap::MinHeap(){

}

MinHeap::MinHeap(int capacity){
	
	this->size = 0;
	this->capacity = capacity;
	this->array = new MinHeapNode* [capacity];
	this->position = new int[capacity];

}

MinHeap::~MinHeap(){
	delete position;

	for(int i=0; i < capacity; i++){
		delete array[i];
	}
}

void MinHeap::swapMinHeapNode(MinHeapNode** first, MinHeapNode** second){
	MinHeapNode* temp = *first;
	*first = *second;
	*second = temp;
}

void MinHeap::MinHeapify(int index){

	int smallest, left, right;
	smallest = index;
	left =  2 * index + 1;
	right = 2 * index + 2;

	if((left < size) && (array[left]->distance < array[smallest]->distance)){
		smallest = left;
	}
	if((right < size) && (array[right]->distance < array[smallest]->distance)){
		smallest = right;
	}
	if(smallest != index){
		MinHeapNode *smallestNode = array[smallest];
		MinHeapNode *indexNode = array[index];

		position[smallestNode->vertex] = index;
		position[indexNode->vertex] = smallest;

		swapMinHeapNode(&array[smallest], &array[index]);

		MinHeapify(smallest);

	}
}

int MinHeap::isEmpty(){
	return size == 0;
}

MinHeapNode* MinHeap::extractMin(){

	if(this->isEmpty()){
		return NULL;
	}

	MinHeapNode* root = array[0];

	MinHeapNode* lastNode = array[size-1];
	array[0] = lastNode;

	position[root->vertex] = size-1;
	position[lastNode->vertex] = 0;

	--size;
	MinHeapify(0);

	return root;

}

void MinHeap::decreaseKey(int vertex, int distance){

	int i = position[vertex];

	array[i]->distance = distance;

	while(i && array[i]->distance < array[(i-1)/2]->distance){

		position[array[i]->vertex] = (i-1)/2;
		position[array[(i-1)/2]->vertex] = i;

		swapMinHeapNode(&array[i], &array[(i-1)/2]);

		i = (i-1)/2;
	}
}

bool MinHeap::inMinHeap(int v){
	if(position[v] < size){
		return true;
	}
	return false;
}






