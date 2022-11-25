//#include <iostream>
//#include <WinSock2.h>
//#include <thread>
//#include <string>
//
//using namespace std;
//
//#pragma comment(lib,"ws2_32.lib")
//
//#define PACKET_SIZE 1024
//
//template <typename T>
//class Vec {
//private:
//	int size, maxsize;
//	T* data = NULL;
//
//public:
//	Vec() :size(0), maxsize(1), data(0) {}
//	~Vec() { size = 0; maxsize = 1; delete[]data; }
//	
//	void push_back(T t) {
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
//	int length() { return this->length; }
//	T& operator[](int index) { return data[index]; }
//};
//
//class ClientSock {
//public:
//	SOCKET Client;
//	SOCKADDR_IN client_info = { 0 };
//	int client_size = sizeof(client_info);
//	string username;
//
//	ClientSock(string username) : username(username) {
//		Client = { 0 };
//		client_info = { 0 };
//		client_size = sizeof(client_info);
//	}
//	~ClientSock() {
//		Client = { 0 };
//		client_info = { 0 };
//		client_size = -1;
//		username = "";
//	}
//};
//
//class Rooms {
//private:
//	char *room_name; //规 捞抚
//	char* user_name[99];//规狼 立加磊甸
//	int user_count,max_user;
//
//public:
//	Rooms(char *room_name) : room_name(room_name),user_name(0),user_count(0),max_user(1) {} //规积己
//	~Rooms() { delete[]user_name; }
//
//	void push(string u_name) {
//		if (user_count + 1 >= max_user) {
//			max_user *= 2;
//			char* tmp[];
//			for (int i = 0; i < user_count; i++) tmp[i] = user_name[i];
//		}
//	}
//
//};
//
//typedef struct {
//	int User_Id;
//	char User_Name[100];
//	int Room_Id;
//};