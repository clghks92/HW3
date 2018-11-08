#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <stdlib.h>

#define SIZE 124
#define PRIOR 10

//2014726094_김치환

struct {
	long type;
	char data[SIZE];
}msg_data;

int main()
{
	int msqid, data_len;
	
	if((msqid = msgget((key_t)1234, IPC_CREAT|0666)) == -1){
		perror("msgget failed");
		exit(1);
	}

	
	while(1){
		if((data_len = msgrcv(msqid, &msg_data, SIZE, (-1*PRIOR), IPC_NOWAIT)) ==-1)
		{
			if(errno == ENOMSG) {
				printf("no message\n");
				break;

			}
			perror("msgrcv failed\n");
			exit(1);
	
		}

		msg_data.data[data_len] = '\0';
		printf("data : %s[%ld]\n", msg_data.data, msg_data.type);
	}

	if(msgctl(msqid, IPC_RMID, 0) == -1) {
                perror("msgctl failed");
                exit(1);
        }
	exit(0);
}

	
