#include "Graph.hpp"

#include <iostream>
#include <stdlib.h>
#include <climits>
#include <fstream>
#include <vector>
#include <algorithm>

Graph::Graph(){
	
}


Graph::~Graph(){
	/*for(int i=0; i < this->n; i++){
		array[i].~List();
	}*/
}

void splitString(std::vector<int>& vector, std::string& line){
	int i = 0;
	std::string index;

	while(line[i] != '\0'){

		int no;
		if(line[i] == ' '){ /* Or " ," for comma, check COW for the updates */
			no = atoi(index.std::string::c_str());
			index.clear();
			vector.push_back(no);
		}
		else if(line[i+1] == '\0'){ /* To make sure if the lines in the input file */
			index += line[i];		/*  does not have space before the end of the line */
			no = atoi(index.std::string::c_str());
			index.clear();
			vector.push_back(no);
		}
		else{
			index += line[i];
		}

		i++;
	}
}


void PrintVector(std::vector<int>& v){
	int i = 0;
	while(i < v.size()){
		std::cout << v[i] << std::endl;
		i++;
	}
}

Graph::Graph(const std::string& inputFileName){
	std::ifstream inputFileStream;

	inputFileStream.open(inputFileName.std::string::c_str(), std::ifstream::in);

	std::string line;
	
	std::getline(inputFileStream, line);
	this->n = atoi(line.std::string::c_str());

	//this->array = (List*) malloc(n * sizeof(List));
	// Change this line as below:
	this->array = new List [n];
        
	for (int j = 0; j < n; j++){
		this->array[j].head = NULL;
	}
	
	std::getline(inputFileStream, line);
	this->numberofDest = atoi(line.std::string::c_str());


	std::getline(inputFileStream, line);
	splitString(this->warehouses, line);


	std::getline(inputFileStream, line);
	splitString(this->destinations, line);


	int vertex = 0;

	while(!inputFileStream.eof()){

		std::getline(inputFileStream, line);

		std::vector<int> index;
		splitString(index, line);
		
		int i = 0;

		while(i < index.size()){
			if(index[i] != 0){
				addEdge(vertex, i, index[i]);
				//std::cout << "adding edge " << vertex << "  " << i << "  " << "  " << index[i] << std::endl;
			}

			i++;
		}

		vertex++;
		
	}

	inputFileStream.close(); 

}


/* Adds to the beginning of the related adjacency list */
/* NOTE: Adds to two different adjacency lists to be able to construct a undirected graph */
void Graph::addEdge(int source, int destination, int weight){

	ListNode* newNode = new ListNode(destination, weight);
	newNode->next = array[source].head;
	array[source].head = newNode;
	/*
	newNode = new ListNode(source, weight);
	newNode->next = array[destination].head;
	array[destination].head = newNode;*/
}

/* Dijkstra's Algorithm */
std::vector<int> Graph::Dijkstra(int source){

	int vertices = this->n;
	std::vector<int> distance(vertices);

	MinHeap* minHeap = new MinHeap(vertices);

	for(int v=0; v < vertices; ++v){

		distance[v] = INT_MAX;

		minHeap->array[v] = new MinHeapNode(v, distance[v]);
		minHeap->position[v] = v;

	}

	minHeap->array[source] = new MinHeapNode(source, distance[source]);
	minHeap->position[source] = source;
	distance[source] = 0;

	minHeap->decreaseKey(source, distance[source]);

	minHeap->size = vertices;



	while(!minHeap->isEmpty()){

		MinHeapNode* minHeapNode = minHeap->extractMin();

		int u = minHeapNode->vertex;


		ListNode* ptrListNode = array[u].head;

		while(ptrListNode != NULL){

			int v = ptrListNode->destination;


			if((minHeap->inMinHeap(v)) && (distance[u] != INT_MAX) && (ptrListNode->weight + distance[u] < distance[v])){
				
				distance[v] = distance[u] + ptrListNode->weight;

				minHeap->decreaseKey(v, distance[v]);
			}

			ptrListNode = ptrListNode->next;
		}
	}

	//this->dijkstra = distance;
	/*
	std::cout << std::endl;
	for(int k=0; k<n; k++){
		std::cout << distance[k] << std::endl;
	}
	*/
	return distance;
}


void Graph::PrintGraphList(){

	int i = 0;
	while(i < n){
		ListNode* temp = array[i].head;

		std::cout << i << "th list:" << std::endl;

		while(temp != NULL){
			std::cout << "weight: " << temp->weight << "  destination: " << temp->destination << std::endl;
			temp = temp->next;			
		}

		i++;
	}
}


bool maximumSize(std::vector<int> i, std::vector<int> j){ 
	return (i[0] > j[0]);
}

bool minimumSize(std::vector<int> i, std::vector<int> j){ 
	return (i[0] < j[0]);
}

void printOutput(std::vector <std::vector <int> >& result){
	
	int size = result.size();
	
	for(int i=0; i < size; i++){
		std::cout << result[i][0] << " " << result[i][1] << std::endl;
	}
}

void Graph::outputDestinations(){
	
	std::vector<int> first = Dijkstra(warehouses[0]);
	std::vector<int> second = Dijkstra(warehouses[1]);

	std::vector< std::vector<int> > allPaths;

	for(int i=0; i < n; i++){
		if(find(destinations.begin(), destinations.end(), i) != destinations.end()){
			std::vector<int> pair;
		
			if(first[i] < second[i]){
				pair.push_back(-(first[i]-second[i])); /* Store as absolute value of difference */
				pair.push_back(first[i]);
				pair.push_back(warehouses[0]);
				pair.push_back(second[i]);
				pair.push_back(warehouses[1]);
			}
			else{
				pair.push_back(first[i]-second[i]); /* Store as absolute value of difference */	
				pair.push_back(second[i]);
				pair.push_back(warehouses[1]);
				pair.push_back(first[i]);
				pair.push_back(warehouses[0]);
			}

			pair.push_back(i);
			allPaths.push_back(pair);
		}
	}

	sort(allPaths.begin(), allPaths.end(), maximumSize);

	int size = allPaths.size();
	int total = 0;
	int firstw = size/2;
	int secondw = size/2;
	std::vector< std::vector<int> > resultSet;

	for(int j = 0; j < size; j++){
		
		std::vector<int> subset;

		if(((firstw == 0) && (allPaths[j][2] == warehouses[0])) || 
			((secondw == 0) && (allPaths[j][2] == warehouses[1]))){
			/* There is no choice other than taking the larger path */
			total += allPaths[j][3];
			subset.push_back(allPaths[j][5]);
			subset.push_back(allPaths[j][4]);

			if(allPaths[j][4] == warehouses[0]){
				firstw--;
			}
			else{
				secondw--;
			}
		}
		else{
			total += allPaths[j][1];
			subset.push_back(allPaths[j][5]);
			subset.push_back(allPaths[j][2]);

			if(allPaths[j][2] == warehouses[0]){
				firstw--;
			}
			else{
				secondw--;
			}
		}

		resultSet.push_back(subset);
		
	}

	sort(resultSet.begin(), resultSet.end(), minimumSize);
	
	std::cout << total << std::endl;
	printOutput(resultSet);
}











