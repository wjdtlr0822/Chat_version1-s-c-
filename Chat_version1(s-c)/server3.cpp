//클라이언트를 무한대로 받을 수 있도록 수정

#include <iostream>
#include <cstring>
#include <WinSock2.h>
#include<thread>
#include <vector>


#pragma comment(lib, "ws2_32.lib")

#define PACKET_SIZE 1024
using namespace std;

SOCKET skt;

class Socket {
public:
	SOCKET client;
	SOCKADDR_IN client_in = {};
	int client_size = sizeof(client_in);
	int number;

	Socket() {
		client = { 0 };
		client_in = { 0 };
		client_size = sizeof(client_in);
	}
	~Socket() {
		client = { 0 };
		client_in = { 0 };
		client_size = -1;
		number = -1;
	}
};

vector<Socket> s;

void recv_server(SOCKET s,int num) {
	char buffer[PACKET_SIZE];
	cout << num << "님 입장" << endl;
	while (true) {
		ZeroMemory(buffer, PACKET_SIZE);
		recv(s, buffer, PACKET_SIZE, 0);
		if (WSAGetLastError()) {
			cout << num << ".[퇴장]" << endl;
			return;
		}
		cout << num << "님의 메세지 : " << buffer << endl;
	}
}

void acceptClient() {
	int number = 0;
	while (1) {
		s.push_back(Socket());
		s[number].client = accept(skt, (SOCKADDR*)&s[number].client_in, &s[number].client_size);
		s[number].number = number;

		thread (recv_server, s[number].client, number).detach();
		number++;
	}
}
int main() {
	WSADATA wsa;
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
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(8888);
	addr.sin_family = AF_INET;

	bind(skt, (SOCKADDR*)&addr, sizeof(addr));
	listen(skt, SOMAXCONN);

	thread (acceptClient).detach();

	while (true);

	closesocket(skt);
	WSACleanup();
}