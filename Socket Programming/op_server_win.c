#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define BUF_SIZE 1024
#define OPSZ 4
void ErrorHandling(char *message);
void ShowSocketBufSize(SOCKET sock);

int main(int argc, char *argv[])
{
	WSADATA wsaData;
	SOCKET hServSock;
	char opinfo[BUF_SIZE];
	int recvCnt;
	int result, opndCnt, i;
	SOCKADDR_IN servAdr, clntAdr;
	int clntAdrSize;

	int setbuf[2];

	int sndBuf, rcvBuf, state, len, tmpSndBuf, tmpRcvBuf = 0;

	if(argc!=2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	} 
	
	if(WSAStartup(MAKEWORD(2, 2), &wsaData)!=0)
		ErrorHandling("WSAStartup() error!"); 
	
	hServSock=socket(PF_INET, SOCK_DGRAM, 0);
	if(hServSock==INVALID_SOCKET)
		ErrorHandling("UDP socket creation error");
	
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family=AF_INET;
	servAdr.sin_addr.s_addr=htonl(INADDR_ANY);
	servAdr.sin_port=htons(atoi(argv[1]));
	
	if(bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr))==SOCKET_ERROR)
		ErrorHandling("bind() error");
	
	clntAdrSize=sizeof(clntAdr);

			//�۽Ź���Ȯ��
			len=sizeof(sndBuf);
			state=getsockopt(hServSock, SOL_SOCKET, SO_SNDBUF, (char*)&sndBuf, &len);
			if(state==SOCKET_ERROR)
				ErrorHandling("getsockopt() error");
			//���Ź���Ȯ��
			len=sizeof(rcvBuf);
			state=getsockopt(hServSock, SOL_SOCKET, SO_RCVBUF, (char*)&rcvBuf, &len);
			if(state==SOCKET_ERROR)
				ErrorHandling("getsockopt() error");

	//Ŭ���̾�Ʈ�κ��� ���� ��Ŷ �޽����� �м�( ���� ���� ũ�� Ȯ�� or ������ ��� )
	recvCnt = recvfrom(hServSock, opinfo, BUF_SIZE-1, 0, (SOCKADDR*)&clntAdr, &clntAdrSize);		
	opndCnt = opinfo[0];
	printf("���ø�ɾ� ����. \n\n");

		switch(opndCnt)
		{
		//Ȯ���� ��� 
		case 1 :
			//Ȯ�ε� �۽Ź��ۿ� ���Ź��� ���� Ŭ���̾�Ʈ�� ����
			sendto(hServSock, (char*)&rcvBuf, sizeof(rcvBuf), 0, (SOCKADDR*)&clntAdr, clntAdrSize);
			sendto(hServSock, (char*)&sndBuf, sizeof(sndBuf), 0, (SOCKADDR*)&clntAdr, clntAdrSize);
			printf("��,���Ź��� ����. \n\n");
			break;
		
		//������ ���
		case 2 :	
			//�۽Ź���Ȯ��
			len=sizeof(sndBuf);
			state=getsockopt(hServSock, SOL_SOCKET, SO_SNDBUF, (char*)&sndBuf, &len);
			if(state==SOCKET_ERROR)
				ErrorHandling("getsockopt() error");
			//���Ź���Ȯ��
			len=sizeof(rcvBuf);
			state=getsockopt(hServSock, SOL_SOCKET, SO_RCVBUF, (char*)&rcvBuf, &len);
			if(state==SOCKET_ERROR)
				ErrorHandling("getsockopt() error");
			//�۽Ź��ۼ���
			state=setsockopt(hServSock, SOL_SOCKET, SO_SNDBUF, (char*)&sndBuf, sizeof(sndBuf));
			if(state==SOCKET_ERROR)
			ErrorHandling("setsockopt() error!");
			//���Ź��ۼ���
			state=setsockopt(hServSock, SOL_SOCKET, SO_RCVBUF, (char*)&rcvBuf, sizeof(rcvBuf));
			if(state==SOCKET_ERROR)
			ErrorHandling("setsockopt() error!");

			//Ŭ���̾�Ʈ���� ��,���� ���� ũ�� ������ �ӽ� ����
			setbuf[0] = *( (int*) (&opinfo[1]) );
			setbuf[1] = *( (int*) (&opinfo[5]) );

			//���޵� �ۼ��� ���� ũ�Ⱚ���� ���� �ۼ��� ���� ũ�⸦ ����
			sndBuf = setbuf[0];
			rcvBuf = setbuf[1];

			//ȭ�鿡 ���
			printf("������ �۽� ���� ũ�� : %d \n", sndBuf);
			printf("������ ���� ���� ũ�� : %d \n\n", rcvBuf);
			
		}

	closesocket(hServSock);
	WSACleanup();
	return 0;
}



void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}