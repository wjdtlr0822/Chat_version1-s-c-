//#include<iostream>
//#include<WinSock2.h>
//#include <thread>
//#include <string>
//
//#pragma comment(lib, "ws2_32.lib")
//
//using namespace std;
//
//#define PACKET_SIZE 1024
//
//void recv_data(SOCKET& s) {
//	char buffer[PACKET_SIZE];
//	while (true) {
//		ZeroMemory(buffer, PACKET_SIZE);
//		recv(s, buffer, PACKET_SIZE, 0);
//		if (WSAGetLastError()) break; //�������ᰨ��.
//		cout << "\n���� �޼��� : " << buffer << endl << "���� �޼��� : ";
//	}
//}
//
//void openSocket() {
//	WSADATA wsa;
//	if (WSAStartup(MAKEWORD(2, 2), &wsa)) {
//		cout << "WSA error" << endl;
//		WSACleanup();
//		return;
//	}
//	SOCKET skt = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
//	if (skt == INVALID_SOCKET) {
//		cout << "socket error" << endl;
//		closesocket(skt);
//		WSACleanup();
//		return;
//	}
//
//	SOCKADDR_IN addr = {};
//	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
//	addr.sin_family = AF_INET;
//	addr.sin_port = htons(8888);
//
//	while (connect(skt, (SOCKADDR*)&addr, sizeof(addr)));
//	
//	char buffer[PACKET_SIZE];
//
//	recv(skt, buffer, PACKET_SIZE, 0);
//	int mynum = atoi(buffer);
//	sprintf(buffer, "[%d] %s::%d", mynum, inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
//
//	thread(recv_data, ref(skt)).detach();
//	//SetConsoleTitle(buffer);
//
//	while (!WSAGetLastError()) {
//		cout << "���� �޼��� : ";
//		cin >> buffer;
//
//		send(skt, buffer, strlen(buffer), 0);
//	}
//
//	closesocket(skt);
//	WSACleanup();
//}
//
//int main() {
//	openSocket();
//	return 0;
//}