/*
 * Reads users input and searches for an executable with a matching name.
 * If it finds a matches a child process will be created and it will run
 * the executable. Then the parent process will kill off the child process.
 * If the user types "exit" program will quit. Program will continue to
 * run in a forever until this condition is met.
*/

#include<unistd.h>
#include<sys/wait.h>
#include<cstring>
#include<string>
#include<iostream>

using namespace std;

int main()
{
	bool check=true;
	std::string command;
	std::string exit = "exit";//phrase to exit
	while(check)//infinite loop
	{
		std::cout<<"Input command name or 'exit' to quit"<<endl;//ask user for input
		std::cin>>command;//input for exit or name of process
		if(strcmp(command.c_str(),exit.c_str())==0)//check for exit match
		{
			check=false;//update bool
			break;//break out of loop
		}
		if(fork()==0)//child code
		{
			execve(command.c_str(),NULL,0);//execute chosen process
			break;
		}
		else//parent code
		{
			int status;
			waitpid(-1, &status, 0);//kill child
		}
	}
	return 0;
}
