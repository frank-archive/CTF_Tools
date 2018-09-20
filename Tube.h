#pragma once
#include<string>
#include<WinSock2.h>
#pragma comment(lib,"Ws2_32.lib ")

void setTubeLogLevel(int l);

class RemoteSession {
	SOCKET sock;
	bool closed;
public:

	RemoteSession(std::string host, int port);
	~RemoteSession();
	void interactive();

	std::string recv(int bytes = 4096, time_t timeout = 0);
	std::string recvall(time_t timeout = 0);
	std::string recvline(bool keepends = true);
	std::string recvuntil(std::string pattern, bool drop);

	void send(std::string data);
	void sendline(std::string data);

	void close();
	bool isClosed();
};
class ProcessSession {
	void interactive();

	std::string recv(int bytes = 4096);
	std::string recvall();
	std::string recvline(bool keepends = true);
	std::string recvuntil(std::string pattern, bool drop);

	void send(std::string data);
	void sendline(std::string data);

	void close();
};
class Listen_Session {

};
RemoteSession remote(std::string addr, int port);
ProcessSession process(std::string proc);
Listen_Session listen();