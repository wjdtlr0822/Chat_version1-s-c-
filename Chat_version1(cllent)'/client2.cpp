#include<iostream>
#include<WinSock2.h>
#include <thread>
#include <string>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

#define PACKET_SIZE 1024


int main() {
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa)) {
		cout << "WSA error" << endl;
		WSACleanup();
		return 0;
	}
	SOCKET skt = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (skt == INVALID_SOCKET) {
		cout << "socket error" << endl;
		closesocket(skt);
		WSACleanup();
	}

	SOCKADDR_IN addr = {};
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);

	while (connect(skt, (SOCKADDR*)&addr, sizeof(addr)));

	char buffer[PACKET_SIZE];

	recv(skt, buffer, PACKET_SIZE, 0);
	int mynum = atoi(buffer);
	sprintf(buffer, "[%d] %s::%d", mynum, inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));

	//SetConsoleTitle(buffer);

	while (!WSAGetLastError()) {}

	closesocket(skt);
	WSACleanup();

}