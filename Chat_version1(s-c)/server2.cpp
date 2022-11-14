#include <iostream>
#include <WinSock2.h>
#include <thread>
#include <string>

#pragma comment(lib,"ws2_32.lib")

using namespace std;

#define PACKET_SIZE 1024
#define MAX 10

WSADATA wsa;
SOCKET skt, client_sock[MAX];
SOCKADDR_IN client[MAX] = { 0 };
int client_size[MAX];



void error(SOCKET skt) {
	closesocket(skt);
	WSACleanup();
}

void recvclient(SOCKET& s, int client_num) {

}

void acceptclient() {
	char client_num[10];
	for (int i = 0; i < MAX; i++) {
		client_size[i] = sizeof(client[i]);
		client_sock[i] = accept(skt, (SOCKADDR*)&client[i], &client_size[i]);
		if (client_sock[i] == INVALID_SOCKET) {
			cout << "accept error" << endl;
			error(client_sock[i]);
			return;
		}

		cout << "Cient #" << i << " Join!!!" << endl;
		ZeroMemory(client_num, sizeof(client_num));
		_itoa_s(i, client_num, 10); //i의 정수값을 client_num에 10진수로 저장
		send(client_sock[i], client_num, strlen(client_num), 0);
		thread(recvclient, ref(client_sock[i]), i).detach();
	}
}


int main() {
	WSAStartup(MAKEWORD(2, 2), &wsa);

	skt = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (skt == INVALID_SOCKET) {
		cout << "socket error" << endl;
		error(skt);
		return;
	}

	SOCKADDR_IN addr = {};
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);

	if (bind(skt, (SOCKADDR*)&addr, sizeof(addr))) {
		cout << "bind error " << endl;
		error(skt);
		return;
	}

	if (listen(skt, SOMAXCONN)) {
		cout << "listen error" << endl;
		error(skt);
		return;
	}

	thread(acceptclient).detach();

	while (1) {}

}