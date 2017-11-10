/*
 * Recursively creates a process tree with 8 processes. Each parent can't have
 * more than 2 children.
 * The 8 children are recursively generated with each parent only having one child.
 * Return up the stack if the count is 8 becuase this is the end of the tree.
 *	Tree layout:
 *	0
 *	|
 *	1
 *	|
 *	2
 *	|
 *	3
 *	|
 *	4
 *	|
 *	5
 *	|
 *	6
 *	|
 *	7
 *	|
 *	8
 */
#include<unistd.h>
#include<sys/wait.h>
#include<iostream>
#include<cstring>

using namespace std;

void printfunc()//Prints out current process labelled as child and parent process of current
{
	std::cout<<"Child: "<<getpid()<<" Parent: "<<getppid()<<endl;
	return;
}

void recursion(int count)//Recursively generates a new child from previous process
{
	if(count==8)//Ends recursion after 8th child is made
	{
		return;
	}
	else
	{
		count++;//update count before creating new process
		if(fork()==0)//create new process
		{
			printfunc();//print out child and parent
			recursion(count);//recursive call to create new function
		}
		else//parent code to kill child
		{
			int status;
			waitpid(-1,&status,0);
		}
	}
}

int main()
{
	int count=0;//initialize count
	recursion(count);//call function to generate the fork tree
	return 0;
}
