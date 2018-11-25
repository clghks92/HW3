#include "MySem.h" 
#include "MyShm.h"
#include <signal.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/sem.h> 
#include <sys/shm.h>
#include <sys/types.h>

#define BUFSIZE 100

void signalHandler(int signum);

int shmid = 0;
char *shmaddr;

int semidServ = 0;
int semidClnt = 0;

int main(int argc, char const *argv[]){
	char send[BUFSIZE];

	shmid = openShm(MY_SHM_KEY);
	shmaddr = shmat(shmid, NULL, 0);

	semidServ = openSem(MY_SEM_SERV_KEY);
	semidClnt = openSem(MY_SEM_CLNT_KEY);

	signal(SIGINT, signalHandler);

	while(1){
		printf("송신할 메시지를 적어주세요.(bye to quit): ");
		scanf("%s", send);
		fflush(stdin);
		fflush(stdout);
		if(strcmp(send, "bye") == 0){
			shmdt(shmaddr);
			exit(0);
		}

		lockSem(semidClnt);
		memcpy(shmaddr, send, sizeof(send));
		unlockSem(semidServ);
	}

	return 0;
}

void signalHandler(int signum){
	if(signum == SIGINT){
		shmdt(shmaddr);
		exit(0);
	}
}




