/*
 * Recursively creates a process tree with 12 processes. Each parent can't have
 * more than 3 or less than 2 children.
 *					Tree Layout:
 *						0
 *			/			|			\
 *			1			2			3
 *		/	|	 \	/	|	\	/	|	\
 *		2	3	4	3	4	5	4	5	6
 *	Creates a fork tree depth first each with 3 children. Special cases are count==2 and ==3
 *	because there are parts of the tree where they are both a parent and a child at the
 *	end of the tree. If they are a child of the root and count 2 or 3 then it will create more
 *	child processes. If not a child of the root then return up the stack because this an end point
 *	of the tree. For count==4,5,6 return up the stack because these are always the end of the tree.
 */
#include<unistd.h>
#include<sys/wait.h>
#include<iostream>
#include<cstring>

using namespace std;

int dforks=3;//number of desired forks
int f2=0;//flag to check for when a process 2 is a child of the root 
int f3=0;//flag to check for when a process 3 is a child of the root
int p;//stores process 0's id

void printfunc()//Prints out current labelled as child and parent of child
{
	std::cout<<"Child: "<<getpid()<<" Parent: "<<getppid()<<endl;
	return;
}

void recursion(int count)
{
	if(count==4 || count==5 || count==6)//these are end points in the tree
	{
		return;
	}
	if(count==2 && p==getppid())//when count is 2 and is a child of process 0
	{
		f2=1;//update flag continue to make children
	}
	if(count==2 && f2==0)//when not a direct child of 0 and count 2
	{
		return;//end of tree
	}
	if(count==3 && p==getppid())//chen count is 3 and is a child of process 0
	{
		f3=1;//update flag continue to make children
	}
	if(count==3 && f3==0)//when not a direct child of 0 and count 3
	{
		return;//end of tree
	}
	else
	{
		for(int i=0;i<dforks;i++)//create children of main 
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
	p = getpid();//get top process' id
	recursion(count);//call recursive function to create fork tree
	return 0;
}
