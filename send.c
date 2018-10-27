#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct mymsgbuf {
	long mtype;
	char mtext[80];

};

int main(void){
	key_t key;
	int msgid;
	struct mymsgbuf mesg;
	char *str = "exit";


	
	key = ftok("keyfile", 1);
	msgid = msgget(key, IPC_CREAT|0644);
	
	if(msgid == -1){
		perror("msgget");
		exit(1);
	}
	
	while(1)
	{
		mesg.mtype = 1;
		printf("송신할 메시지를 적어주세요.(exit 입력시 종료): ");
		scanf("%s", mesg.mtext);
		
	        
		if(strcmp(mesg.mtext, str) == 0){
		        msgctl(msgid, IPC_RMID, (struct msqid_ds*)NULL);
			exit(1);

		}
		if(msgsnd(msgid, (void*)&mesg, 80, IPC_NOWAIT) == -1)
		{
			perror("msgsnd");
			exit(1);
		}
	}



	return 0;
}
