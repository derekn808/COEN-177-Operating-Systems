#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

#define MAX_MEMORY_SIZE 500

struct pageReference
{
	int page;
	int count;
};

int isInMemory(int page, struct pageReference pageTable[], int tableSize){
	int i;
	for(i=0;i<tableSize;i++){
		if(pageTable[i].page == page){
			pageTable[i].count++;
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
				pageTable[pageTableIndex].count=0;
			}
			else{
				int j=pageRequest;
				int LFU=0;
				int least=pageTable[0].count;
				for(int i=0;i<tableSize;i++){
					if(pageTable[i].count<least){
						least=pageTable[i].count;
						LFU=i;
					}
				}
				for(int i=LFU;i<tableSize;i++){
					pageTable[i].page=pageTable[i+1].page;
					pageTable[i].count=pageTable[i+1].count;
				}
				pageTable[tableSize-1].page=j;
				pageTable[tableSize-1].count=0;

			}
		}
	}

	return 0;
}
