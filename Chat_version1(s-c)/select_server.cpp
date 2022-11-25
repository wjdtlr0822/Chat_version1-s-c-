//#pragma comment(lib,"ws2_32")
//#define _WINSOCK_DEPRECATED_NO_WARNINGS
//
//#include <iostream>
//#include <winsock2.h> 
//#include <stdio.h>
//#include<memory>
//
//#define MAX_LINE 1024 
//#define BACKLOG 5
//
//using namespace std;
//
//int main(int argc, char** argv)
//{
//	WSADATA wsa;
//
//	//server
//	SOCKET serverSocket;
//	SOCKADDR_IN listen_addr, accept_addr;
//	char buf[MAX_LINE];
//	fd_set temp_fds, read_fds;
//
//	int readn, addr_len;
//	unsigned int i, fd_num = 0;
//
//	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
//		return 1;
//	}
//
//	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	if (serverSocket == INVALID_SOCKET) return 1;
//
//	memset((void*)&listen_addr, 0x00, sizeof(listen_addr));// ù��° ���� : �޸��� �����ּ� 
//																							//�ι�° ���� : ���� ��
//																							//����° ���� : size
//
//	listen_addr.sin_family = AF_INET;
//	listen_addr.sin_port = htons(8888);
//	listen_addr.sin_addr.s_addr = htonl(INADDR_ANY);
//
//	if (bind(serverSocket, (SOCKADDR*)&listen_addr, sizeof(listen_addr)) == SOCKET_ERROR) return 1;
//	if (listen(serverSocket, BACKLOG) == SOCKET_ERROR) return 1;
//
//	FD_ZERO(&read_fds); // fds�ʱ�ȭ
//	FD_SET(serverSocket, &read_fds); //serverSocket�� read_fds�� �߰��Ѵ�.
//	cout << "Ŭ���̾�Ʈ ���� �����...." << endl;
//
//	while (1) {
//		//select�Լ��� ȣ��Ϸ� �Ǹ�, ��ȭ�� fd���� �̿��� ���� �ʱ�ȭ�� �ȴ�.
//		//���� ������ fd_set �����͸� temp_fds�� �����ؾ��Ѵ�.(���ʿ��� �� fd_set���� ����)
//
//		temp_fds = read_fds;
//
//		// �� �ٸ� Ÿ�Ӿƿ��� �����Ƿ�, select�Լ��� �Է��� ���������� blocking�Ǿ� ����Ѵ�.
//		fd_num = select(0, &temp_fds, NULL, NULL, NULL);
//
//		for (i = 0; i <= temp_fds.fd_count; i++) {
//			SOCKET currentSocket = temp_fds.fd_array[i];//?
//
//			if (FD_ISSET(currentSocket, &temp_fds)) { //?
//				if (currentSocket == serverSocket) { //���ο����� ������ ���{
//					addr_len = sizeof(SOCKADDR_IN);//?
//					cout << "���ο� ������ ������ �Խ��ϴ�" << endl;
//
//					SOCKET clientSocket = accept(serverSocket, (SOCKADDR*)&accept_addr,&addr_len);
//					if (clientSocket == INVALID_SOCKET) { cout << "socket_error" << endl; continue; }
//					FD_SET(clientSocket, &read_fds);
//
//				}
//				else {//������ �̹� ����� �������κ��� �޽����� ���� ��
//					memset(buf, 0x00, MAX_LINE);
//					readn = recv(currentSocket, buf, MAX_LINE, 0);
//					if (readn <= 0) {
//						cout << "Ŭ���̾�Ʈ���� ������ ����Ǿ����ϴ�." << endl;
//						closesocket(currentSocket);
//						FD_CLR(currentSocket, &read_fds);
//					}
//					else {
//						cout << buf << "�޼��� ������" << endl;
//						send(currentSocket, buf, readn, 0);
//					}
//				}
//				if (--fd_num <= 0) break;
//			}
//		}
//	}
//	closesocket(serverSocket);
//	WSACleanup();
//	return 0;
//}
//
//
///*
//1.��ũ���� ����
//2.�˻� ���� ����
//3. Ÿ�� �ƿ� ����
//4. select�Լ� ȣ��
//5.���Ȯ��
//*/
//
//
////int select(int nfds, fd_set* restrict readfds, fd_set* restrict writefds, fd_set* restrict errorfds, struct timeval* restrict timeout);
////nfds ���� : ���� �׽�Ʈ�� ��ũ���� ����. 0~(nfds - 1) ������ �׽�Ʈ �Ѵ�. // �����쿡���� �׻� 0
////readfds ���� : null����Ʈ�� �ƴϸ� �Է��� ������ ǥ���ϴ� fd_set ��.
////writefds ���� : null����Ʈ�� �ƴϸ� ����� ������ ǥ���ϴ� fd_set��
////errorfds ���� : null�����Ͱ� �ƴϸ� ������ ������ ǥ���ϴ� fd_set��
////timeout ���� : null�̸� ��ȭ�� ���� ������ ��� ���(��ŷ), �ƴϸ� ���� �ð� ����� �ð� �ʰ� ���ϵ�.
//
//
//
////============================����ó��==================================
////���� ó���� ���� ���� errno�� ����Ǹ�, ���н� - 1 ���� ��ȯ�� �Ǹ� errno�� ������ �Ǵ��մϴ�.�׷��⿡ ���� �߻��� �����ϰ� ������ ���� �޽��� ����ϰ� �ʹٸ� ������ ���� �ϸ� �˴ϴ�.
////
////if (select(...) < 0) {
////	perror("select"); // ���� ���
////	... // ���� ó��
////}
//
//
//
////================================����Ʈ������ ����� �����ϴ� ��ũ��================
////void FD_ZERO(fd_set* fdset);
////void FD_CLR(int fd, fd_set* fdset);
////void FD_SET(int fd, fd_set* fdset);
////int FD_ISSET(int fd, fd_set* fdset);
////FD_ZERO�� fdset�� �ִ� ��� ���� 0���� �ʱ�ȭ�մϴ�.������ �����ϸ� �ʱ�ȭ�ϴ� ���� �翬�մϴ�.ó�� fd_set�� ������ �ݵ�� ȣ���ؾ� �մϴ�.
////FD_CLR�� fdset�� ������ fd�� �ش� �ϴ� ��Ʈ(0���� �����ϱ⿡ ������ fd - 1��Ʈ)�� 0���� Ŭ�����մϴ�.
////FD_SET�� fdset�� ������ fd�� �ش� �ϴ� ��Ʈ(0���� �����ϱ⿡ ������ fd - 1��Ʈ)�� 1���� �����մϴ�.
////FD_ISSET�� fdset�� ������ fd�� �ش� �ϴ� ��Ʈ(0���� �����ϱ⿡ ������ fd - 1��Ʈ)�� 1�� �����Ǿ����� Ȯ���մϴ�.��, 1�� �����Ǿ��ٸ� 1�� ��ȯ, 0���� �����Ǿ��ٸ� 0���� ��ȯ�մϴ�.