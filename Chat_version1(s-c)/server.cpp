#include <iostream>
#include <WinSock2.h>
#include <thread>

#pragma comment(lib,"ws2_32.lib")

using namespace std;

#define PACKET_SIZE 1024

SOCKET skt, client_sock;


void proc_recvs() {
	char buffer[PACKET_SIZE] = {};

	while (!WSAGetLastError()) {
		ZeroMemory(&buffer, PACKET_SIZE);
		recv(client_sock, buffer, PACKET_SIZE, 0);
		cout << "Client�� ���� ���� �޼��� : " << buffer << endl;
		cout << "���� �޼��� : ";
	}
}

int main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	cout << "WSADATA ����!!" << endl;

	skt = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN addr = {};
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);

	cout << "bind ����!!" << endl;
	bind(skt, (SOCKADDR*)&addr, sizeof(addr));
	listen(skt, SOMAXCONN);

	SOCKADDR_IN client = {};
	int client_size = sizeof(client);
	ZeroMemory(&client, client_size);

	client_sock = accept(skt, (SOCKADDR*)&client, &client_size);

	cout << "client ����!!" << endl;

	char buffer[PACKET_SIZE] = { 0 };
	thread proc1(proc_recvs);

	while (!WSAGetLastError()) {
		cout << "���� �޼��� : ";
		cin >> buffer;
		send(client_sock, buffer, strlen(buffer), 0);
	}
	proc1.join();

	closesocket(client_sock);
	closesocket(skt);
	WSACleanup();
}