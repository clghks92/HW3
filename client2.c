#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define PERMS 0666

int main(){
        int fd1, fd2;

        char *str = "bye";
        char *fifo1 = "fifo1";
        char *fifo2 = "fifo2";

        char msg1[80], msg2[80];

        mkfifo(fifo1, PERMS);
        fd2 = open(fifo1, O_RDWR);

        fd1 = open(fifo2, O_RDWR);

        while(1){
                printf("client2(input): ");
                scanf("%s", msg1);

                write(fd1, msg1, 80);

                if(strcmp(str, msg1) == 0){
                        unlink(fifo1);
                        exit(1);
                }

                read(fd2, msg2, 80);

	      	if(strcmp(str, msg2) == 0){
                        unlink(fifo1);
                        exit(1);
                }

                printf("client1 say: %s\n", msg2);
        }
        return 0;
}




