//#include <iostream>
//#include<WinSock2.h>
//#include <thread>
//
//using namespace std;
//
//#pragma comment(lib,"ws2_32.lib")
//
//#define PACKET_SIZE 1024
//
////vector를 대신해서 사용할 LIFO
//template <typename T>
//class dpVec {
//private:
//	int size, maxsize;
//	T* data = NULL;
//	
//public:
//	dpVec() : size(0), maxsize(1), data(0) {}
//	~dpVec() { size = 0; maxsize = 1; delete[]data; }
//
//	void push(T t) {
//		if (size + 1 >= maxsize) {
//			maxsize *= 2;
//			T* tmp = new T[maxsize];
//			for (int i = 0; i < size; i++) tmp[i] = data[i];
//			tmp[size++] = t;
//			delete[]data;
//			data = tmp;
//		}
//		else data[size++] = t;
//	}
//
//	int length() const { return this->size; }
//	T& operator[](const int index) { return data[index]; }
//};
//
//typedef struct {
//	int mNum; //보낸 클라이언트의 번호
//	int hNum; //받을 클라이언트의 번호
//	char hMessage[PACKET_SIZE]; //메세지
//}PacketInfo;
//
//class dpSock {
//public:
//	SOCKET client;
//	SOCKADDR_IN client_info = { 0 };
//	int client_size = sizeof(client_info);
//	int number;
//	dpSock() {
//		client = { 0 };
//		client_info = { 0 };
//		client_size = sizeof(client_info);
//	}
//	~dpSock() {
//		client = { 0 };
//		client_info = { 0 };
//		client_size = -1;
//		number = -1;
//	}
//};
//
//dpVec<dpSock> s; //소켓 클라이언트 리스트
//dpVec<PacketInfo> pkInfo; // 클라이언트 패킷 리스트
//
//
//void recvData(SOCKET sock, int num) {
//	char buf[PACKET_SIZE];
//	cout << num << "[ 입장 ]" << endl;
//	while (true) {
//		recv(sock, buf, PACKET_SIZE, 0);
//		memcpy((char*)&pkInfo[num], buf, PACKET_SIZE);//struct <- char*값 복사
//		if (WSAGetLastError()) {
//			cout << num << "퇴장" << endl;
//			return;
//		}
//
//		if (pkInfo[num].hNum != -1 && pkInfo[num].hNum <= s.length() - 2) {//대상 존재
//			cout << "[ " << num << "] -> [" << pkInfo[num].hNum << "] : " << pkInfo[num].hMessage << endl;
//			send(s[pkInfo[num].hNum].client, buf, PACKET_SIZE,0);
//		}
//
//		else if (pkInfo[num].hNum != -1 && pkInfo[num].hNum > s.length() - 2) {
//			cout << "[" << num << "] -> [X] : " << pkInfo[num].hMessage << endl;
//			send(s[pkInfo[num].hNum].client, buf, PACKET_SIZE, 0);
//		}
//		else {
//			cout << "[" << num << "] -> [ALL] : " << pkInfo[num].hMessage << endl;
//			for (int i = 0; i < s.length(); i++) send(s[i].client, buf, PACKET_SIZE, 0);
//		}
//	}
//}
//
//void acceptClient(SOCKET server) {
//	int number = 0;
//	char dsf[100] = { 0 };
//	while (true) {
//		s.push(dpSock()); //클라이언트 소켓 생성
//		pkInfo.push(PacketInfo()); //클라이언트패킷정보 생성
//		s[number].client = accept(server, (SOCKADDR*)&s[number].client_info, &s[number].client_size);
//		s[number].number = number;
//		_itoa_s(number, dsf, 10); //number의 값을 char형태로 dsf에 저장
//		send(s[number].client, dsf, strlen(dsf), 0);
//		thread(recvData, s[number].client, number).detach();
//		number++;
//	}
//}
//
//int main() {
//	WSADATA wsa;
//	WSAStartup(MAKEWORD(2, 2), &wsa);
//
//	SOCKET server = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
//
//	SOCKADDR_IN addr = {};
//	addr.sin_addr.s_addr = htonl(INADDR_ANY);
//	addr.sin_port = htons(8888);
//	addr.sin_family = AF_INET;
//
//	bind(server, (SOCKADDR*)&addr, sizeof(addr));
//	listen(server, SOMAXCONN);
//	cout << "서버 시작!!!" << endl;
//
//	thread(acceptClient, ref(server)).detach();
//
//	while (true);
//	closesocket(server);
//	WSACleanup();
//}