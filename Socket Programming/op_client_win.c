#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define BUF_SIZE 1024
#define RLT_SIZE 4
#define OPSZ 4
void ErrorHandling(char *message);

int main(int argc, char *argv[])
{
	WSADATA wsaData;
	SOCKET hSocket;
	int result, opndCnt, i;
	char opmsg[BUF_SIZE];
	SOCKADDR_IN servAdr;

	int sndBuf, rcvBuf, state, len = 0;
	

	if(argc!=3) {
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	
	if(WSAStartup(MAKEWORD(2, 2), &wsaData)!=0)
		ErrorHandling("WSAStartup() error!"); 

	hSocket=socket(PF_INET, SOCK_DGRAM, 0);   	
	if(hSocket==INVALID_SOCKET)
		ErrorHandling("socket() error");
	
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family=AF_INET;
	servAdr.sin_addr.s_addr=inet_addr(argv[1]);
	servAdr.sin_port=htons(atoi(argv[2]));		

	//���� ���� ���� ũ�⸦ Ȯ���Ұ��� �����Ұ��� ����
	fputs("Ȯ��=1 or ����=2 �Է� \n", stdout);
	scanf("%d", &opndCnt);
	opmsg[0] = (char)opndCnt;

	//Ȯ���� ��
	if( opmsg[0] == 1 ) {
		
		//���� ���� ũ�� Ȯ�� ��ɾ ������ ����
		sendto(hSocket, opmsg, sizeof(opmsg), 0, (SOCKADDR*)&servAdr, sizeof(servAdr));
		printf("Ȯ�� ��ɾ� ����\n");

		//�����κ��� ���޵� ��,���� ���� ũ��
		recv(hSocket, (char*)&rcvBuf, sizeof(rcvBuf), 0);
		recv(hSocket, (char*)&sndBuf, sizeof(sndBuf), 0);

		//ȭ�鿡 ���
		printf("�۽� ���� ũ�� : %d \n", sndBuf);
		printf("���� ���� ũ�� : %d \n\n\n", rcvBuf);
	}

	//������ ��
	if( opmsg[0] == 2 ) {
		printf("\n");

		//���ϴ� ���� ���� ũ�⸦ �߰��� �Է�
		printf("ù��°�� �۽� ���۸� �Է�. \n");
		printf("�ι�°�� ���� ���۸� �Է�. \n\n");
		for(i=0; i<2; i++)
		{
			printf("���� ũ�� �Է�  : ");
			scanf("%d", (int*)&opmsg[i*OPSZ+1]);
		}

		//������ ���� ���� ���� ��ɾ�(2) �� ��,���� ���� ũ�� ������ ���� ����
		sendto(hSocket, opmsg, sizeof(opmsg), 0, (SOCKADDR*)&servAdr, sizeof(servAdr));
			printf("\n������ ����. \n");	
	}	

	closesocket(hSocket);
	WSACleanup();
	return 0;
}

void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}