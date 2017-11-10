#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>

using namespace std;

#define MAX_MEMORY_SIZE 500

struct pageReference
{
	int page;
	int clock;
};

int isInMemory(int page, struct pageReference pageTable[], int tableSize){
	int i;
	for(i=0;i<tableSize;i++){
		if(pageTable[i].page == page){
			pageTable[i].clock=(int) time(NULL);
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
	struct pageReference pageTable[MAX_MEMORY_SIZE];
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
				pageTable[pageTableIndex++].page=pageRequest;
				pageTable[pageTableIndex].clock=(int) time(NULL);
			}
			else{
				int j=pageRequest;
				int LRU=0;
				int oldest=pageTable[0].clock;
				for(int i=0;i<tableSize;i++){
					if(pageTable[i].clock<oldest){
						oldest=pageTable[i].clock;
						LRU=i;
					}
				}
				for(int i=LRU;i<tableSize;i++){
					pageTable[i].page=pageTable[i+1].page;
					pageTable[i].clock=pageTable[i+1].clock;
				}
				pageTable[tableSize-1].page=j;
				pageTable[tableSize-1].clock=(int) time(NULL);
			}
		}
	}

	return 0;
}
