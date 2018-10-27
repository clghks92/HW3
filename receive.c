#include <sys/msg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct mymsgbuf {
        long mtype;
        char mtext[80];
};

int main(void){
	struct mymsgbuf inmsg;
	key_t key;
	int msgid;
	char *str1 = "exit";

	key = ftok("keyfile", 1);
	if((msgid = msgget(key, 0)) < 0)
	{
		perror("msgget");
		exit(1);
	}

	while(1){

	if( msgrcv(msgid, &inmsg, 80, 0, 0) == -1){

		perror("msgrcv");
		exit(1);

	}

	if(strcmp(inmsg.mtext, str1) == 0)
	{
		printf("종료되었습니다");
		exit(1);
	}

	
	  printf("메시지를 수신하였습니다. 내용은[%s]입니다\n", inmsg.mtext);
	
	


	}



        return 0; 	


}


