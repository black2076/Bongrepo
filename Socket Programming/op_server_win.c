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

			//송신버퍼확인
			len=sizeof(sndBuf);
			state=getsockopt(hServSock, SOL_SOCKET, SO_SNDBUF, (char*)&sndBuf, &len);
			if(state==SOCKET_ERROR)
				ErrorHandling("getsockopt() error");
			//수신버퍼확인
			len=sizeof(rcvBuf);
			state=getsockopt(hServSock, SOL_SOCKET, SO_RCVBUF, (char*)&rcvBuf, &len);
			if(state==SOCKET_ERROR)
				ErrorHandling("getsockopt() error");

	//클라이언트로부터 받은 패킷 메시지를 분석( 소켓 버퍼 크기 확인 or 설정인 경우 )
	recvCnt = recvfrom(hServSock, opinfo, BUF_SIZE-1, 0, (SOCKADDR*)&clntAdr, &clntAdrSize);		
	opndCnt = opinfo[0];
	printf("선택명령어 수신. \n\n");

		switch(opndCnt)
		{
		//확인일 경우 
		case 1 :
			//확인된 송신버퍼와 수신버퍼 값을 클라이언트로 전송
			sendto(hServSock, (char*)&rcvBuf, sizeof(rcvBuf), 0, (SOCKADDR*)&clntAdr, clntAdrSize);
			sendto(hServSock, (char*)&sndBuf, sizeof(sndBuf), 0, (SOCKADDR*)&clntAdr, clntAdrSize);
			printf("송,수신버퍼 전송. \n\n");
			break;
		
		//설정일 경우
		case 2 :	
			//송신버퍼확인
			len=sizeof(sndBuf);
			state=getsockopt(hServSock, SOL_SOCKET, SO_SNDBUF, (char*)&sndBuf, &len);
			if(state==SOCKET_ERROR)
				ErrorHandling("getsockopt() error");
			//수신버퍼확인
			len=sizeof(rcvBuf);
			state=getsockopt(hServSock, SOL_SOCKET, SO_RCVBUF, (char*)&rcvBuf, &len);
			if(state==SOCKET_ERROR)
				ErrorHandling("getsockopt() error");
			//송신버퍼설정
			state=setsockopt(hServSock, SOL_SOCKET, SO_SNDBUF, (char*)&sndBuf, sizeof(sndBuf));
			if(state==SOCKET_ERROR)
			ErrorHandling("setsockopt() error!");
			//수신버퍼설정
			state=setsockopt(hServSock, SOL_SOCKET, SO_RCVBUF, (char*)&rcvBuf, sizeof(rcvBuf));
			if(state==SOCKET_ERROR)
			ErrorHandling("setsockopt() error!");

			//클라이언트에서 송,수신 버퍼 크기 정보를 임시 저장
			setbuf[0] = *( (int*) (&opinfo[1]) );
			setbuf[1] = *( (int*) (&opinfo[5]) );

			//전달된 송수신 버퍼 크기값으로 소켓 송수신 버퍼 크기를 설정
			sndBuf = setbuf[0];
			rcvBuf = setbuf[1];

			//화면에 출력
			printf("설정된 송신 버퍼 크기 : %d \n", sndBuf);
			printf("설정된 수신 버퍼 크기 : %d \n\n", rcvBuf);
			
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