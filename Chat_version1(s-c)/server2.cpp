//#include <iostream>
//#include <WinSock2.h>
//#include <thread>
//#include <string>
//
//#pragma comment(lib,"ws2_32.lib")
//
//using namespace std;
//
//#define PACKET_SIZE 1024
//
//WSADATA wsa;
//SOCKET skt, *client_sock;
//SOCKADDR_IN *client;
//int *client_size,MAX;
//
//
//void error(SOCKET &s) {
//	closesocket(s);
//	WSACleanup();
//}
//
//void recvclient(SOCKET& s, int client_num) {
//	char buf[PACKET_SIZE];
//
//	while (true) {
//		ZeroMemory(buf, PACKET_SIZE);
//		if (recv(s, buf, PACKET_SIZE, 0) == -1) break;
//		cout << "\nClient # " << client_num << " : " << buf << "\n보낼 데이터 입력 : ";
//	}
//	return;
//}
//
//void acceptclient() {
//	char client_num[10];
//	for (int i = 0; i < MAX; i++) {
//		client_size[i] = sizeof(client[i]);
//		client_sock[i] = accept(skt, (SOCKADDR*)&client[i], &client_size[i]);
//
//		if (client_sock[i] == INVALID_SOCKET) {
//			cout << "accept error" << endl;
//			closesocket(skt);
//			error(client_sock[i]);
//			return;
//		}
//
//		cout << "Cient #" << i << " Join!!!" << endl;
//		ZeroMemory(client_num, sizeof(client_num));
//		_itoa_s(i, client_num, 10); //i의 정수값을 client_num에 10진수로 저장
//		send(client_sock[i], client_num, strlen(client_num), 0);
//		thread(recvclient, ref(client_sock[i]), i).detach();
//	}
//}
//
//void openSocket() {
//	if (WSAStartup(MAKEWORD(2, 2), &wsa)) {
//		cout << "WSA error" << endl;
//		return;
//	}
//
//	skt = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
//	if (skt == INVALID_SOCKET) {
//		cout << "socket error" << endl;
//		error(skt);
//		return;
//	}
//
//	SOCKADDR_IN addr = {};
//	addr.sin_addr.s_addr = htonl(INADDR_ANY);
//	addr.sin_family = AF_INET;
//	addr.sin_port = htons(8888);
//
//	if (bind(skt, (SOCKADDR*)&addr, sizeof(addr))) {
//		cout << "bind error " << endl;
//		error(skt);
//		return;
//	}
//
//	if (listen(skt, SOMAXCONN)) {
//		cout << "listen error" << endl;
//		error(skt);
//		return;
//	}
//
//	thread(acceptclient).detach();
//
//	char msg[PACKET_SIZE];
//	while (true) {
//		cout << "보낼 메세지 입력 >> ";
//		cin >> msg;
//		
//		for (int i = 0; i < MAX; i++) {
//			send(client_sock[i], msg, strlen(msg), 0);
//		}
//	}
//	for (int i = 0; i < MAX; i++) closesocket(client_sock[i]);
//	closesocket(skt);
//	WSACleanup();
//	return;
//}
//
//int main() {
//	cout << "최대 클라이언트 수 : ";
//	cin >> MAX;
//
//	client_sock = new SOCKET[MAX];
//	client = new SOCKADDR_IN[MAX];
//	client_size = new int[MAX];
//
//	ZeroMemory(client_sock, sizeof(client_sock));
//	ZeroMemory(client, sizeof(client));
//	ZeroMemory(client_size, sizeof(client_size));
//
//	openSocket();
//
//	delete[] client_sock, client, client_size;
//	return 0;
//}