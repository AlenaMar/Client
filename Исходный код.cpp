#include <stdio.h>

#pragma comment(lib,"Ws2_32.lib")

#include <sys/types.h>
#include <WinSock2.h>
#include <iostream>
#include <Ws2tcpip.h> 
#include <locale.h>
#include <stdint.h> //для типа int32_t 

int main(int args, char **argv)
{
	setlocale(LC_ALL, "russian");

	WSAData ws;
	WSAStartup(MAKEWORD(2, 2), &ws);

	int SOCKET = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct sockaddr_in SOCKADDR;
	SOCKADDR.sin_family = AF_INET;
	SOCKADDR.sin_port = htons(12345);
	SOCKADDR.sin_addr.s_addr = htonl(INADDR_LOOPBACK); //htonl(INADDR_LOOPBACK); inet_addr("127.0.0.1");

	int resultconnect = connect(SOCKET, (struct sockaddr *)(&SOCKADDR), sizeof(SOCKADDR)); /*присоединились*/
	if (resultconnect != 0)
	{
		printf("FALL!!! connect = %d\n", resultconnect);
		//DWORD er = WSAGetLastError();
		//printf("%d",er);
		//printf("\n");
	}
	else
	{
		printf("connect = %d\n",resultconnect);
		printf("Присоединились к серверу!\n");
	}

	char Message [] = "WelcomeToHell";

	int32_t messageLen = htonl(sizeof(Message)); /*находим длину передаваемого сообщения, htonl переворачивает байты в сетевой порядок*/
	send(SOCKET, (char *)&messageLen, sizeof(messageLen), NULL);

	send(SOCKET, Message, 4, NULL);
	//printf("Сообщение отправлено! ");

	recv(SOCKET, (char *)&messageLen, sizeof(messageLen), NULL); /*принимаем заголовок известной длинны*/

	recv(SOCKET, Message, 4, NULL);

	shutdown(SOCKET, SD_BOTH);
	closesocket(SOCKET);

	//printf("%s\n", Buffer);

	getchar ();

	return 0;
}