#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>


int main(void)
{
	pid_t pid;

	pid = fork();

	if(pid==-1)
	{
		printf("fork fail");
	        exit(0);
	}

	else if(pid == 0) // child process
	{
		printf("Child process\n");
		printf("C=%d", getpid());
		exit(0);
	}
	else //parent process
	{
		printf("Parent Process\n");
		printf("C=%d", getpid());
		exit(0);
	}
}
