#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFSIZE 1024

size_t get_file_size(const char*file_name){
	struct stat stat_info;
	if( stat(file_name, &stat_info) != 0)
	{
		printf("i can't find file\n");
		return -1;
	}
	return stat_info.st_size;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

int main(int argc, char **argv)
{
	int serv_sock;
	int clnt_sock;
	char sbuf[BUFSIZE];
	char cbuf[BUFSIZE];
	int str_len;
	int len;
	int fd;

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	int clnt_addr_size;

	if(argc != 2){
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1)
		error_handling("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) ==-1)
		error_handling("bind() error");

	if(listen(serv_sock, 5) == -1)
		error_handling("listen() error");



	while(1)
	{
		clnt_addr_size = sizeof(clnt_addr);
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
		if(clnt_sock == -1)
			error_handling("accept() error");


		len = read(clnt_sock, cbuf, BUFSIZE);
		printf("file[%s]을 전송받았습니다\n", cbuf);
		

		fd = open(cbuf, O_CREAT|O_WRONLY|O_TRUNC);

		str_len = read(clnt_sock, sbuf, BUFSIZE);
		printf("file size : %d\n", str_len);

		write(fd, sbuf, sizeof(sbuf));





		close(fd);
		close(clnt_sock);
	}
	return 0;
}



































