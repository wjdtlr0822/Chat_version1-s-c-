#include <iostream>
#include <WinSock2.h>
#include <string>

#pragma comment(lib,"ws2_32")

#define BUF_SIZE 100

using namespace std;

void error_handling(string s);

int main(int argc, char* argv[]) {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET serv_sock, clnt_sock;
	SOCKADDR_IN serv_addr, clnt_addr;
	TIMEVAL timeout;

	FD_SET reads, cpy_reads;

	int adr_sz;
	int fd_max, str_len, fd_num;
	char buf[BUF_SIZE];

	if (argc != 2) {
		cout << "Usage : " << argv[0] << endl;
		exit(1);
	}

	serv_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(8888);

	if (bind(serv_sock, (SOCKADDR*)&serv_addr, sizeof(serv_addr)) == -1) error_handling("bind() error");
	if (listen(serv_sock, 5) == -1) error_handling("listen() error");

	FD_ZERO(&reads);
	FD_SET(serv_sock, &reads);

	while (1) {
		cpy_reads = reads;
		timeout.tv_sec = 5;
		timeout.tv_usec = 5000;

		if ((fd_num = select(0, &cpy_reads, NULL, NULL, &timeout)) == -1) break;
		if (fd_num == 0) continue;

		for (int i = 0; i < cpy_reads.fd_count; i++) {

			SOCKET currentSocket = cpy_reads.fd_array[i];
			
			if (FD_ISSET(currentSocket, &cpy_reads)) //fd_set 테이블을 검사한다.
				// 서버 소켓(리스닝 소켓)에 이벤트(연결 요청) 발생
			{
				if (currentSocket == serv_sock) {
					adr_sz = sizeof(clnt_addr);
					clnt_sock = accept(serv_sock, (SOCKADDR*)&clnt_addr, &adr_sz);
					
					if (clnt_sock == INVALID_SOCKET) {
						cout << "잘못된 소켓입니다" << endl; continue;
					}
					FD_SET(clnt_sock, &reads);
					
				//	if (fd_max < clnt_sock) fd_max = clnt_sock;
				//	cout << "connected client : " << clnt_sock << endl;
				}

				else { //기존에 이미 연결된 소켓으로 부터 메세지를 받을 때
					str_len = recv(currentSocket, buf, BUF_SIZE,0);
					if (str_len <= 0) {
						FD_CLR(i, &reads);
						closesocket(i);
						cout << "closed client : " << i << endl;
					}
					else {
						cout << buf << endl;
						send(currentSocket, buf, str_len,0);
					}
				}
			}
		}
	}

	closesocket(serv_sock);
	WSACleanup();
	return 0;
}

void error_handling(string s) {
	cout << s << endl;
	exit(1);
}