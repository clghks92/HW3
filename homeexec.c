#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int pid;
	pid = fork();

	if(pid==-1)
	{
		printf("exec failed");
		exit(-1);
	}

	else if(pid==0) // child process
	{
		execl("/bin/ls", "ls", "-1", (char*) 0);
		printf("exec success");
		exit(0);
	}
	else // parent process
	{
	
		printf("ls completed\n");
		exit(0);
	}
}

