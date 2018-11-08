#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define SIZE 124

//2014726094_김치환

struct{
	long type;
	char data[SIZE];
}msg_data;

int main()
{
	
	int msqid, data_len;
	char buffer[SIZE];
	char *str = "quit";
      

	if((msqid = msgget((key_t)1234, IPC_CREAT|0666)) == -1){
		perror("msgget failed");
		exit(1);

	}
	// 키의 메시지 큐 생성 
	while(1){
		printf("input data => ");
		scanf("%s", buffer);

		if(strcmp(buffer, str) == 0){
			break;
		} //입력받은 내용이 ‘quit’이면 while 문 벗어남 

		printf("input priority => ");
		scanf("%ld", &(msg_data.type));
		strcpy(msg_data.data, buffer); 

		if(msgsnd(msqid, &msg_data, strlen(msg_data.data), IPC_NOWAIT) == -1){
			perror("msgsnd");
			exit(1);
		}
	}
	exit(0);
}

		
