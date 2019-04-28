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

	//현재 소켓 버퍼 크기를 확인할건지 설정할건지 선택
	fputs("확인=1 or 설정=2 입력 \n", stdout);
	scanf("%d", &opndCnt);
	opmsg[0] = (char)opndCnt;

	//확인할 때
	if( opmsg[0] == 1 ) {
		
		//소켓 버퍼 크기 확인 명령어를 서버로 전달
		sendto(hSocket, opmsg, sizeof(opmsg), 0, (SOCKADDR*)&servAdr, sizeof(servAdr));
		printf("확인 명령어 전송\n");

		//서버로부터 전달된 송,수신 버퍼 크기
		recv(hSocket, (char*)&rcvBuf, sizeof(rcvBuf), 0);
		recv(hSocket, (char*)&sndBuf, sizeof(sndBuf), 0);

		//화면에 출력
		printf("송신 버퍼 크기 : %d \n", sndBuf);
		printf("수신 버퍼 크기 : %d \n\n\n", rcvBuf);
	}

	//설정할 때
	if( opmsg[0] == 2 ) {
		printf("\n");

		//원하는 소켓 버퍼 크기를 추가로 입력
		printf("첫번째는 송신 버퍼를 입력. \n");
		printf("두번째는 수신 버퍼를 입력. \n\n");
		for(i=0; i<2; i++)
		{
			printf("버퍼 크기 입력  : ");
			scanf("%d", (int*)&opmsg[i*OPSZ+1]);
		}

		//서버로 소켓 버퍼 설정 명령어(2) 와 송,수신 버퍼 크기 정보를 같이 전달
		sendto(hSocket, opmsg, sizeof(opmsg), 0, (SOCKADDR*)&servAdr, sizeof(servAdr));
			printf("\n설정값 전송. \n");	
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