#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>

#define BUFSIZE 1024

void error_handling(char *message)
{
      fputs(message, stderr);
      fputc('\n', stderr);
      exit(1);
}


int main(int argc, char **argv)
{
	int sock;
	char sbuf[BUFSIZE];
	char cbuf[BUFSIZE];
	int str_len;
	int len;
	struct sockaddr_in serv_addr;
	char name[BUFSIZE];
	int fd;
	

	if(argc != 3){
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	sock=socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
		error_handling("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));
	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		error_handling("connect() error!");

	while(1){
		fputs("전송할 파일 이름을 입력하세요 (bye to quit) : ", stdout);
		fgets(name, BUFSIZE, stdin);

		if(strcmp(name, "bye\n") == 0)
			break;
		printf("file[%s]을 전송하였습니다\n", name);

		write(sock, name, strlen(name));

		fd = open(name, O_RDONLY);

		if(fd == -1)
			error_handling("file open error");

		while((len = read(fd, cbuf, BUFSIZE)) != 0)
		{
			write(sock, cbuf, len);
		}

		close(fd);
                close(sock);
	}

	return 0;
	
}














