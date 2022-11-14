#include <iostream>
#include <WinSock2.h>
#include <thread>
#include <string>

#pragma comment(lib,"ws2_32.lib")

#define PACKET_SIZE 1024

using namespace std;

SOCKET skt;

void proc_recv() {
	char buffer[PACKET_SIZE] = {};
	string cmd;
	while (!WSAGetLastError()) {
		ZeroMemory(&buffer, PACKET_SIZE);
		recv(skt, buffer, PACKET_SIZE, 0);
		cmd = buffer;
		if (cmd == "exit") break;
		cout << "Server로 부터 받은 메세지 :" << buffer << endl;
		cout << " 보낼 메세지 >> ";
	}
}

int main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	cout << "WSADATA 시작!!" << endl;

	skt = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN addr = {};
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);

	while (1) {
		cout << "대기중!!!" << endl;
		if (!connect(skt, (SOCKADDR*)&addr, sizeof(addr))) break;
	}
	thread proc1(proc_recv);

	char msg[PACKET_SIZE] = {};
	while (!WSAGetLastError()) {
		cout << "보낼 메세지 >> ";
		cin >> msg;
		send(skt, msg, strlen(msg), 0);
	}
	proc1.join();


	closesocket(skt);
	WSACleanup();
}