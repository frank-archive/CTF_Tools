#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include"Tube.h"
#include"Logger.h"
#include<iostream>
using namespace std;
bool WSAStarted;
WSADATA w_data;
pwn::RemoteSession::RemoteSession(std::string host, int port) {
	Logger tlog;
	tlog.progress("Opening connection to %s on port %d\n", host.c_str(), port);
	if (WSAStarted == false)
		WSAStartup(MAKEWORD(2, 2), &w_data), WSAStarted = true;

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN addrServ;
	addrServ.sin_family = AF_INET;
	addrServ.sin_port = port;

	hostent *hostInfo = gethostbyname(host.c_str());
	if (hostInfo == NULL) {
		tlog.error("host not found...destructing...\n");
		RemoteSession::~RemoteSession();
		return;
	}
	addrServ.sin_addr = *((IN_ADDR*)hostInfo->h_addr);
	tlog.success("Open connection to %s on port %d done\n", host.c_str(), port);
}

pwn::RemoteSession::~RemoteSession() {
	if (WSAStarted == true)
		WSACleanup(), WSAStarted = false;
	closesocket(sock);
}

void pwn::RemoteSession::interactive() {
	cout << ("--------------\nentering remote interactive mode...\ninput \'exit\' to exit(\'exit\'will be sent too\n\n");
	std::string data;
	while (1) {
		cout << ">";
		cin >> data;
		sendline(data);
		if (data == "exit")break;
		cout << recvall();
	}
}

std::string pwn::RemoteSession::recieve(int bytes, time_t timeout){
	Logger tlog; tlog.debug("recieving data\n");
	if (timeout != 0)//set socket recv timeout
		setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));

	char *buffer = new char[bytes]; memset(buffer, 0, sizeof buffer);
	int recieved_bytes;
	if ((recieved_bytes = recv(sock, buffer, bytes - 1, 0))
		== SOCKET_ERROR) {
		delete buffer;
		tlog.info("connection closed by server...destructing\n");
		RemoteSession::~RemoteSession();
	}
	tlog.debug("data recieved %d bytes\n", recieved_bytes);
	string message = buffer; delete buffer;
	return message;
}

std::string pwn::RemoteSession::recvall(time_t timeout) {
	Logger tlog; tlog.debug("recieving all data\n");
	if (timeout != 0)
		setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));

	char buffer[4096]; memset(buffer, 0, sizeof buffer);
	int recieved_bytes = 0; std::string message; int recv_ret;
	while ((recv_ret = recv(sock, buffer, 4095, 0)) > 0) {
		message += buffer; recieved_bytes += recv_ret;
		memset(buffer, 0, sizeof buffer);
	}
	delete buffer;
	if (recv_ret == SOCKET_ERROR) {
		tlog.info("connection closed by server...destructing\n");
		RemoteSession::~RemoteSession();
	}
	tlog.debug("data recieved %d btyes\n", recieved_bytes);
	return message;
}

std::string pwn::RemoteSession::recvline(bool keepends) {
	Logger tlog; tlog.debug("recieving a line of data\n");
	
	return std::string();
}

void pwn::RemoteSession::sendline(std::string data) {

}

pwn::RemoteSession pwn::remote(std::string addr, int port) {
	return RemoteSession(addr, port);
}
