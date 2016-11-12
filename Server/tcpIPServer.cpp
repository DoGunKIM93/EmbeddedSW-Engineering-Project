#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUF_SIZE 50

void error_handling(char *message);
char* transmit_data_new(int clnt_sock, int mission);
int w = 0;

int main(void)
{
	int serv_sock;
	int clnt_sock;

	struct linger solinger = {1, 0};

	struct sockaddr_in serv_adr;
	struct sockaddr_in clnt_adr;
	socklen_t clnt_adr_size;

	char message[BUF_SIZE];
	int i = 0;
	int strLen = 0;

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(setsockopt(serv_sock, SOL_SOCKET, SO_LINGER, &solinger, sizeof(struct linger)) == -1)
		error_handling("setsocketpot(S)_LINGER)");

	if(serv_sock == -1)
		error_handling("socket() error");

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(4002);

	if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("bind() error");

	if (listen(serv_sock, 5) == -1)
		error_handling("listen() error");

	clnt_adr_size = sizeof(clnt_adr);
	clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_size);

	if (clnt_sock == -1)
		error_handling("accept() error");
	else
		printf("Connected client\n");

	while (1)
	{

		strLen = read(clnt_sock, message, BUF_SIZE);

		if (strLen == -1)
		{
			printf("비정상 종료\n");
			//break;
		}
		else if (strLen == 0)
		{
			printf("정상 종료\n");
			break;
		}
		else
			printf("Client to Server : %s", message);

		transmit_data_new(clnt_sock, 15);
	}

	close(clnt_sock);
	close(serv_sock);
	return 0;
}

char* transmit_data_new(int clnt_sock, int mission)
{
	short int temprst;

	int lane_data;
	int mission_data;
	char message1[BUF_SIZE];

	mission_data;

	mission_data = 10;
	sprintf(message1, "%d\n", mission_data);

	write(clnt_sock, message1, BUF_SIZE);
	printf("Server to Client : %s", message1);
	return message1;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
