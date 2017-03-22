#include <stdio.h>

#pragma comment(lib,"Ws2_32.lib")

#include <sys/types.h>
#include <WinSock2.h>
#include <iostream>
#include <Ws2tcpip.h> 
#include <locale.h>
#include <stdint.h> //для типа int32_t 

//функция для проверки на ошибки
void CheckForError (int result)
{

    if (result != 0)
	{
		printf("FALL!!! CheckForError result = %d", result);
		printf("\n");
		exit(0);
	}
}

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

	CheckForError(connect(SOCKET, (struct sockaddr *)(&SOCKADDR), sizeof(SOCKADDR))); /*присоединились*/
	printf("Присоединились к серверу!\n");

	const char message[] = "WelcomeToHell"; //Сообщение
	int32_t sourceLen = strlen(message); //Длина исходного сообщения

	send(SOCKET, (char *)&sourceLen, sizeof(sourceLen), NULL);
	send(SOCKET, message, sourceLen, NULL);
	
	// Принимаем назад
	int32_t destinationLen;
	char messageBuffer[1000];

	if (sizeof(destinationLen) != recv(SOCKET, (char *)&destinationLen, sizeof(destinationLen), NULL))
		exit(1);

	if (destinationLen > sizeof(messageBuffer) - 1)
		destinationLen = sizeof(messageBuffer) - 1;

	if (destinationLen != recv(SOCKET, messageBuffer, destinationLen, NULL))
		exit(1);

	messageBuffer[destinationLen] = 0;
	printf("Полученная строка: '%s'\n", messageBuffer);

	shutdown(SOCKET, SD_BOTH);
	closesocket(SOCKET);

	getchar ();

	return 0;
}