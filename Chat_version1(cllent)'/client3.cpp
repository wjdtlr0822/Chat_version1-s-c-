//클라이언트를 무한대로 받을 수 있도록 수정

#include <iostream>
#include <cstring>
#include <WinSock2.h>
#include<thread>
#include <vector>


#pragma comment(lib, "ws2_32.lib")

#define PACKET_SIZE 1024
using namespace std;

WSADATA wsa;
SOCKET skt;


void recv_client() {
	char buffer[PACKET_SIZE];
	if (recv(skt, buffer, PACKET_SIZE, 0)) {
		cout << "\n받은 메세지 : " << buffer << "\n보낼 메세지 : ";
	}
}

int main() {
	if (WSAStartup(MAKEWORD(2, 2), &wsa)) {
		cout << "WSA Error";
		return -1;
	}

	skt = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (skt == INVALID_SOCKET) {
		cout << "socket error";
		closesocket(skt);
		WSACleanup();
		return -1;
	}

	SOCKADDR_IN addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	while (connect(skt, (SOCKADDR*)&addr, sizeof(addr)));

	char msg[PACKET_SIZE];

	thread(recv_client).detach();
	while (!WSAGetLastError()) {
		cout << "보낼 메세지 입력 : ";
		cin >> msg;
		send(skt, msg, strlen(msg), 0);
	}
}