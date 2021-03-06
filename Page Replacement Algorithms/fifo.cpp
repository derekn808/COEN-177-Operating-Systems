#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <deque>

using namespace std;

#define MAX_MEMORY_SIZE 500

int isInMemory(int page, std::deque<int> pageTable, int tableSize){
	int i;
	for(i=0;i<tableSize;i++){
		if(pageTable[i] == page){
			return 1;
		}
	}
	return 0;
}

int main(int argc, char *argv[])
{
	if(argc<2){
		fprintf(stderr, "Improper usage, please provide page table size\n");
		return 1;
	}
	//stoi is better here
	int tableSize=atoi(argv[1]);
	//sets tableSize to MAX_MEMORY_SIZE if the max is exceeded
	if(tableSize>MAX_MEMORY_SIZE){
		tableSize=MAX_MEMORY_SIZE;
	}
	int pageRequest, pageTableIndex=0;
	std::deque<int> pageTable(tableSize);
	char *input=NULL;
	size_t inputAllocated;
	ssize_t bytesRead;

	while((bytesRead = getline(&input, &inputAllocated, stdin)) !=EOF){
		//stoi is better here
		pageRequest=atoi(input);
		if(pageRequest==0){
		}
		else if(!isInMemory(pageRequest, pageTable, tableSize)){
			fprintf(stdout,"Page number %d caused a page fault.\n", pageRequest);
			if(pageTableIndex<tableSize){
				pageTable[pageTableIndex++]=pageRequest;
			}
			/*if pageTable full then implement page replacement algorithm*/
			else{
				pageTable.pop_front();
				pageTable.push_back(pageRequest);
			}
		}
	}
	
	return 0;
}
