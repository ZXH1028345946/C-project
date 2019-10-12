#include <iostream>
#include <windows.h>
using namespace std;
#pragma comment(lib,"ws2_32.lib")//静态连接库
void main() {
	WORD version = MAKEWORD(2, 2);
	WSADATA socketmsg;
	int err;
	err = WSAStartup(version, &socketmsg);
	if (err != 0) {
		return;
	}
	if (LOBYTE(socketmsg.wVersion) != 2 || HIBYTE(socketmsg.wVersion != 2)) {
		WSACleanup();
		return;
	}
	SOCKET socketserver = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN addrSer, addrCli; 
	addrSer.sin_family = AF_INET;
	addrSer.sin_port = htons(5050);
	addrSer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	bind(socketserver, ( SOCKADDR*)& addrSer, sizeof(SOCKADDR));//绑定套接字 跟服务器的相关地址信息进行绑定
	//监听套接字 5是队列大小
	listen(socketserver, 5);

	SOCKET sockCon;
	int len = sizeof(SOCKADDR);
	cout << "Server wait Client connecting......" << endl;
	sockCon = accept(socketserver, (SOCKADDR*)& addrCli, &len);
	if (sockCon == INVALID_SOCKET) {
		cout << "Server accept client connect fail" << endl;
		return;
	}
	else {
		cout << "Server accept client connect success" << endl;
	}
	char sendbuf[256];
	char recvbuf[256];
	while (1) {
		cout << "Ser:>";
		cin >> sendbuf;
		if (strcmp(sendbuf, "quit") == 0) {
			break;
		}
		send(sockCon, sendbuf, strlen(sendbuf)+1, 0);
		recv(sockCon,recvbuf,256,0);
		cout << "CLI:>" << recvbuf << endl;
	}
	closesocket(socketserver);
	WSACleanup();

}