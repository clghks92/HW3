#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <wait.h>

int sig_count;

int sigchild(){

	pid_t pid;
	int status;
	int spid;

	pid = fork();

	sig_count++;

	if(pid == 0){
		printf("i'm child process : %d\n", getpid());
		printf("<signal_child> : sig_count = %d\n", sig_count);
                printf("pid of sending process = %d\n", getpid());
                printf("uid of sending process = %d\n", getuid());
                printf("Finish homework 3\n");
		sleep(1);
		exit(1);
		execl("home/kimchi123/kill", "kill", "-STOP", NULL);

	}

	else if (pid > 0)
	{
		spid = wait(&status);
	}
	else 
	{
		perror("fork error :");
	}




}



void sig_handler(int signo ){

	


	if(signo == SIGINT){
		sig_count++;
		printf("<signal_int> : sig_count = %d\n", sig_count);
		
	        sigchild();

	



	}
	if(signo == SIGUSR1){
		if(sig_count >= 4)
                {
                        signal(signo, SIG_IGN);
                }


		sig_count++;
		printf("<sig_usr> : sig_count = %d\n", sig_count);

	 

	}
	

        
	return;
}


int main(void)
{


	
	
			
	 
	if(signal(SIGINT, sig_handler) == SIG_ERR){
		return 1;
	}

	if(signal(SIGUSR1, sig_handler) == SIG_ERR){
	

        }

            






	


	while(1){
		pause();
	}

  
	return 0;
}

  









