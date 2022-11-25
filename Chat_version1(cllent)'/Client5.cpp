#include <iostream>
#include<WinSock2.h>
#include<thread>
#include <string>

using namespace std;

#pragma comment(lib,"ws2_32.lib")

atomic<bool> broken(false);


int main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET server = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	SOCKADDR_IN addr = {};
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(8888);
	addr.sin_family = AF_INET;

	while (connect(server, (SOCKADDR*)&addr, sizeof(addr)));
	cout << "서버 접속 성공 " << endl;
	cout << "사용자 이름 : ";
	char username[100];
	cin >> username;

	send(server, username, 100, 0);

	thread(send_msg,ref(server)).detach();
	thread(recv_msg, ref(server)).detach();

	while (!broken.load(memory_order_acquire));

	closesocket(server);
	WSACleanup();

}