#include <stdio.h>

#pragma comment(lib,"Ws2_32.lib")

#include <sys/types.h>
#include <WinSock2.h>
#include <iostream>
#include <Ws2tcpip.h> 
#include <locale.h>
#include <stdint.h> //��� ���� int32_t 
#include <math.h>

//������� ��� �������� �� ������
void CheckForError (int result)
{

    if (result != 0)
	{
		printf("FALL!!! CheckForError result = %d", result);
		printf("\n");
		exit(0);
	}
}

//��������, ������������ �� ���������� ������� (������������ ������)
void fastcall(int p)
{
	bool check = IsDebuggerPresent();
	if (check) {
		printf("���� ��������...\n");
		exit(0);
	}
	else
		printf("��� ���������...\n");
}

int main(int args, char **argv)
{
	setlocale(LC_ALL, "russian");


	//��� ������ ������ ������ ������ ����
	setlocale(LC_ALL, "Russian");
	float t1 = 1.570796;
	char Key[20];
	
	printf("������� ������ ������� � ������: ");
	gets(Key);
	
	int pr = int(Key[0]);
	for (int i = 1; i < strlen(Key); i++)
	{
		pr = pr*int(Key[i]);
	}
	
	float t = atan(pr);
	
	if (abs(t1 - t) < 0.00001)
	{
		printf("***������ ����***\n\n");
	}
	else
	{
		printf("�������� ����\n");
		exit(0);
	}


	WSAData ws;
	WSAStartup(MAKEWORD(2, 2), &ws);

	int SOCKET = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct sockaddr_in SOCKADDR;
	SOCKADDR.sin_family = AF_INET;
	SOCKADDR.sin_port = htons(12345);
	SOCKADDR.sin_addr.s_addr = htonl(INADDR_LOOPBACK); //htonl(INADDR_LOOPBACK); inet_addr("127.0.0.1");
	int iResult;
	iResult = WSAStartup(MAKEWORD(2, 2), &ws);
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;

	// ��������� ip/port
	char iport[] = "";
	char port[] = "";
	printf("������� ip-�����: ");
	gets(iport);
	printf("������� port : ");
	gets(port);
	fastcall(iResult = getaddrinfo(iport, port, &hints, &result));
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	fastcall(connect(SOCKET, (struct sockaddr *)(&SOCKADDR), sizeof(SOCKADDR))); /*��������������*/
	printf("\n");
	printf("   ���������� � �������� �����������!\n");

	const char m1[] = "WelcomeToHell"; //���������  const char message[] = "WelcomeToHell";
	
	const char *message;//
	char vvod[50];//
	printf("      ������� ���������: ");//
	gets(vvod);//
	message = vvod;//

	int32_t sourceLen = strlen(message); //����� ��������� ���������

	send(SOCKET, (char *)&sourceLen, sizeof(sourceLen), NULL);
	send(SOCKET, message, sourceLen, NULL);
	
	// ��������� �����
	int32_t destinationLen;
	char messageBuffer[1000];

	if (sizeof(destinationLen) != recv(SOCKET, (char *)&destinationLen, sizeof(destinationLen), NULL))
		exit(1);

	if (destinationLen > sizeof(messageBuffer) - 1)
		destinationLen = sizeof(messageBuffer) - 1;

	if (destinationLen != recv(SOCKET, messageBuffer, destinationLen, NULL))
		exit(1);

	messageBuffer[destinationLen] = 0;
	printf("      ���������� ������: '%s'\n", messageBuffer);

	shutdown(SOCKET, SD_BOTH);
	closesocket(SOCKET);

	getchar ();

	return 0;
}