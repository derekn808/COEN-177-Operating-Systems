/*
 * Recursively creates a process tree with 17 processes. Each parent can't have
 * more than 3 or less than 2 children.
 *						0
 *				/		|		\
 *				1		2		3
 *			/	|	\/	|	\/	|	\
 *			2	3	43	4	54	5	6
 *		 /	| \					   / \
 *		 3	4  5				  7   8
 *	Creates a fork tree depth first each with 3 children. Special cases are count==2,3,6.
 *	If they are a child of the root and count 3 then it will create more child processes.
 *	If not a child of the root then return up the stack because this an end point.
 *	If it is a child of the root and count 2 then create child processes normally.
 *	If not a child of the root and count 3 then create 3 child processes and return up the stack.
 *	If count==6 then create the remaining 2 processes then return up the stack.
 *	of the tree. For count==4,5 return up the stack because these are always the end of the tree.
 */
#include<unistd.h>
#include<sys/wait.h>
#include<iostream>
#include<cstring>

using namespace std;

int dforks=3;//number of desired forks
int f2=0;//flag to check when a process 2 is a child of root
int f3=0;//flag to check when a process 3 is a child of root
int p;//stores process 0's id

void printfunc()//prints out current id as child and current's parent id
{
	std::cout<<"Child: "<<getpid()<<" Parent: "<<getppid()<<endl;
	return;
}

void recursion(int count)
{
	if(count==4 || count==5)//in all cases these are end of the tree
	{
		return;
	}
	if(count==6)//create last 2 processes at right end of tree
	{
		for(int i=0;i<2;i++)
		{
			if(fork()==0)
			{
				printfunc();
				break;
			}
			else
			{
				int status;
				waitpid(-1,&status,0);
			}
		}
		return;//end of tree return up stack
	}
	if(count==2 && p==getppid())//when count 2 and child of root
	{
		f2=1;//update flag
	}
	if(count==2 && f2==0)//first process with count 2
	{
		for(int i=0;i<3;i++)//create 3 children at left end of tree
		{
			if(fork()==0)
			{
				printfunc();
				break;
			}
			else
			{
				int status;
				waitpid(-1,&status,0);
			}
		}
		return;//go back up stack
	}
	if(count==3 && p==getppid())//when count 3 and direct child of root
	{
		f3=1;//update flag
	}
	if(count==3 && f3==0)//when not a direct child of the root and count 3
	{
		return;//end of tree return up stack
	}
	else
	{
		for(int i=0;i<dforks;i++)//creates 3 children for each process
		{
			count++;//update count
			if(fork()==0)//child code to create new process
			{
				printfunc();
				recursion(count);//recursive call
				break;
			}
			else//parent code to kill child
			{
				int status;
				waitpid(-1,&status,0);
			}
		}
	}
}

int main()
{
	int count=0;//initialize count
	p = getpid();//get process 0's id
	recursion(count);//call recursive funtion to create fork tree
	return 0;
}
