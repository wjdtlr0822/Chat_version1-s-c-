#include<iostream>
#include<WinSock2.h>
#include <thread>

#pragma comment(lib,"ws2_32.lib")

using namespace std;

#define PACKET_SIZE 1024

atomic<bool> broken(false); // ������ ������ Ŭ���̾�Ʈ�� �װ� �����ϰ� �ڵ�����

typedef struct {
	int mNum;
	int hNum;
	char hMessage[PACKET_SIZE];
}PacketInfo;
PacketInfo sendInfo, recvInfo;


void rec(SOCKET server) {
	char buf[PACKET_SIZE] = { 0 };
	while (true) {
		recv(server, buf, PACKET_SIZE, 0);
		memcpy((char*)&recvInfo, buf, PACKET_SIZE);
		if (WSAGetLastError()) {
			broken.store(true, memory_order_release);
			//����� ��� broken�� ������ ����
			return;
		}
		if (recvInfo.hNum != -1) cout << "\n[" << recvInfo.mNum << "] : " << recvInfo.hMessage << endl;
		else cout << "\n[ALL] : " << recvInfo.hMessage << endl;
	}
}

void sendMSG(SOCKET server) {
	char hMessage[PACKET_SIZE] = {0};
	char hNum[100] = { 0 };
	while (true) {
		cout << "�Է� : ";
		cin >> hMessage >> hNum;
		if (atoi(hNum) >= -1) {
			strcpy_s(sendInfo.hMessage, hMessage);
			sendInfo.hNum = atoi(hNum);
			send(server, (char*)&sendInfo, PACKET_SIZE, 0);
		}
	}
}

int main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET server = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN addr = {};
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(8888);
	addr.sin_family = AF_INET;

	while (connect(server, (SOCKADDR*)&addr, sizeof(addr)));

	char mNumc[100] = { 0 };
	recv(server, mNumc, 100, 0);
	sendInfo.mNum = atoi(mNumc);
	cout << "[Client # " << sendInfo.mNum << "] " << endl;
	thread(rec, ref(server)).detach();
	thread(sendMSG, ref(server)).detach();

	while (!broken.load(memory_order_acquire));
	//���� ���� ������ ���� ���
	//atomic �� �˾ƺ���.

	closesocket(server);
	WSACleanup();
}