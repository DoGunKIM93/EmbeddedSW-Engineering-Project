#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 50
#define RLT_SIZE 4
#define OPSZ 4
#define UB (65280)
#define LB (255)

char* transmit_data_new2(int sock, unsigned short _distance);
char* transmit_data_new(int sock, int * mission);

void error_handling(char *message);

int count = 0;
int w = 0;

int main(void) //int argc, char *argv[]
{
	int sock;
	int missionNumber = 2;
	int tempMissionNumber = 2;
	char message[BUF_SIZE];

	char *serv_ip = "127.0.0.1";
	char *serv_port = "4002";
	char * receve_data;
	int i = 0;
	int strLen = 0;

	struct sockaddr_in serv_adr;
	int MissionState[30000] = {0};

	for (i = 0; i < 30000; i++)
		MissionState[i] = i;

	tempMissionNumber = missionNumber;

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1) // 연결 안되었을 경우
		error_handling("socket() error");
	int sockopt = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &sockopt, sizeof(sockopt));

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;					// ipv4
	serv_adr.sin_addr.s_addr = inet_addr(serv_ip);	//ip
	serv_adr.sin_port = htons(atoi(serv_port));		// port

	if (connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)	// 성공시 0, 실패시 -1
		error_handling("connect() error!");
	else
		puts("Connected...........");

	while (1)
	{
		//receve_data = transmit_data_new(sock, MissionState);
		receve_data = transmit_data_new2(sock, 100);

		strLen = read(sock, message, BUF_SIZE);

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
		{
			printf("Server to Clinet : %s", message);
		}
	}

	close(sock);	// 소켓 종료
	return 0;
}

char* transmit_data_new(int sock, int *mission)
{
	short int temprst;

	int lane_data;
	int mission_data;
	char message1[BUF_SIZE];

	mission_data = mission[w];

	w++;
	sprintf(message1, "%d\n", mission_data);

	write(sock, message1, BUF_SIZE);

	return message1;
}

char* transmit_data_new2(int sock, unsigned short _distance)
{
	unsigned char high;
	unsigned char low;
	short int send_data;
	char message1[BUF_SIZE];

	if (count % 3 == 0)
	{
		send_data = 100;
	}
	else if (count % 3 == 1)
	{
		send_data = 200;
	}
	else if (count % 3 == 2)
	{
		send_data = 300;
	}


	high = (send_data&UB) >> 8;
	low = (send_data&LB);

	//sprintf(message1, "S400 %02X%02X000000000001\n", low, high);
	sprintf(message1, "%d\n", send_data);
	printf("Clinet to Server : %d\n", send_data);

	write(sock, message1, BUF_SIZE); //strlen(message1)
	count++;

	return message1;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
