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
//	memset((void*)&listen_addr, 0x00, sizeof(listen_addr));// 첫번째 인자 : 메모리의 시작주소 
//																							//두번째 인자 : 넣을 값
//																							//새번째 인자 : size
//
//	listen_addr.sin_family = AF_INET;
//	listen_addr.sin_port = htons(8888);
//	listen_addr.sin_addr.s_addr = htonl(INADDR_ANY);
//
//	if (bind(serverSocket, (SOCKADDR*)&listen_addr, sizeof(listen_addr)) == SOCKET_ERROR) return 1;
//	if (listen(serverSocket, BACKLOG) == SOCKET_ERROR) return 1;
//
//	FD_ZERO(&read_fds); // fds초기화
//	FD_SET(serverSocket, &read_fds); //serverSocket을 read_fds에 추가한다.
//	cout << "클라이언트 접속 대기중...." << endl;
//
//	while (1) {
//		//select함수가 호출완료 되면, 변화한 fd정보 이외의 것은 초기화가 된다.
//		//따라서 기존의 fd_set 데이터를 temp_fds에 저장해야한다.(최초에는 빈 fd_set값이 저장)
//
//		temp_fds = read_fds;
//
//		// 별 다른 타임아웃이 없으므로, select함수로 입력이 오기전까지 blocking되어 대기한다.
//		fd_num = select(0, &temp_fds, NULL, NULL, NULL);
//
//		for (i = 0; i <= temp_fds.fd_count; i++) {
//			SOCKET currentSocket = temp_fds.fd_array[i];//?
//
//			if (FD_ISSET(currentSocket, &temp_fds)) { //?
//				if (currentSocket == serverSocket) { //새로연결이 들어오는 경우{
//					addr_len = sizeof(SOCKADDR_IN);//?
//					cout << "새로운 소켓의 연결이 왔습니다" << endl;
//
//					SOCKET clientSocket = accept(serverSocket, (SOCKADDR*)&accept_addr,&addr_len);
//					if (clientSocket == INVALID_SOCKET) { cout << "socket_error" << endl; continue; }
//					FD_SET(clientSocket, &read_fds);
//
//				}
//				else {//기존에 이미 연결된 소켓으로부터 메시지를 받을 때
//					memset(buf, 0x00, MAX_LINE);
//					readn = recv(currentSocket, buf, MAX_LINE, 0);
//					if (readn <= 0) {
//						cout << "클라이언트와의 연결이 종료되었습니다." << endl;
//						closesocket(currentSocket);
//						FD_CLR(currentSocket, &read_fds);
//					}
//					else {
//						cout << buf << "메세지 수신함" << endl;
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
//1.디스크립터 설정
//2.검사 범위 설정
//3. 타임 아웃 설정
//4. select함수 호출
//5.결과확인
//*/
//
//
////int select(int nfds, fd_set* restrict readfds, fd_set* restrict writefds, fd_set* restrict errorfds, struct timeval* restrict timeout);
////nfds 인자 : 변경 테스트할 디스크립터 개수. 0~(nfds - 1) 범위을 테스트 한다. // 윈도우에서는 항상 0
////readfds 인자 : null포인트가 아니면 입력이 있음을 표시하는 fd_set 값.
////writefds 인자 : null포인트가 아니면 출력이 있음을 표시하는 fd_set값
////errorfds 인자 : null포인터가 아니면 에러가 있음을 표시하는 fd_set값
////timeout 인자 : null이면 변화가 있을 때까지 계속 대기(블럭킹), 아니면 일정 시간 대기후 시간 초과 리턴됨.
//
//
//
////============================에러처리==================================
////에러 처리는 에러 값은 errno에 저장되며, 실패시 - 1 값이 반환이 되며 errno로 에러를 판단합니다.그렇기에 에러 발생을 감지하고 간단한 에러 메시지 출력하고 싶다면 다음과 같이 하면 됩니다.
////
////if (select(...) < 0) {
////	perror("select"); // 에러 출력
////	... // 에러 처리
////}
//
//
//
////================================시프트연산은 힘드니 제공하는 매크로================
////void FD_ZERO(fd_set* fdset);
////void FD_CLR(int fd, fd_set* fdset);
////void FD_SET(int fd, fd_set* fdset);
////int FD_ISSET(int fd, fd_set* fdset);
////FD_ZERO는 fdset에 있는 모든 값을 0으로 초기화합니다.변수를 선언하면 초기화하는 것은 당연합니다.처음 fd_set를 선언후 반드시 호출해야 합니다.
////FD_CLR는 fdset의 값에서 fd에 해당 하는 비트(0부터 시작하기에 실제는 fd - 1비트)를 0으로 클리어합니다.
////FD_SET는 fdset의 값에서 fd에 해당 하는 비트(0부터 시작하기에 실제는 fd - 1비트)를 1으로 설정합니다.
////FD_ISSET는 fdset의 값에서 fd에 해당 하는 비트(0부터 시작하기에 실제는 fd - 1비트)가 1로 설정되었는지 확인합니다.즉, 1로 설정되었다면 1를 반환, 0으로 설정되었다면 0으로 반환합니다.