#pragma once
#include <stdio.h>
#include <windows.h>
#include <winsock.h>
#include <iostream>
#include <vector>

//#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "wsock32.lib")

class Network
{
private:
	int port;
	char *serverip;
	SOCKET mysocket;
	
public:
	std::vector<SOCKET> client_socket;
	Network(char *_serverip, int _port);
	~Network(void);
	void sockServerConnect(char *ip, int port);
	void sockClientConnect(char *ip, int port);
	SOCKET & getSocket() {return mysocket;};
	SOCKET & getClientSocket() {if (client_socket.size()>0) return client_socket.at(0); };
	int coutClientConnect() { return client_socket.size();};
	void serverListenSocket();
	void closeClientSocket();
};

