#include "Network.h"

Network::Network(char *_serverip, int _port): serverip(_serverip), port(_port) {
  
}


Network::~Network(void) {

}

DWORD WINAPI serverListenThread(LPVOID network) {
	Network netw = ((Network *) network)[0];
	while(1) {
		netw.serverListenSocket();
	}
}

void Network::sockServerConnect(char *ip, int _port) {
	char buff[128];    
	sockaddr_in local_addr;
	

	printf("TCP SERVER DEMO\n");

    if (WSAStartup(0x0202,(WSADATA *) &buff[0])) {
		printf("Error WSAStartup %d\n", WSAGetLastError());
		return;
    }

	if ((mysocket=socket(AF_INET,SOCK_STREAM,0))<0) {
		printf("Error socket %d\n",WSAGetLastError());
		WSACleanup();
		return;
    }

    local_addr.sin_family=AF_INET;
    local_addr.sin_port=htons(port);
    local_addr.sin_addr.s_addr=0;

    if (bind(mysocket,(sockaddr *) &local_addr, sizeof(local_addr))) {
      printf("Error bind %d\n",WSAGetLastError());
      closesocket(mysocket);  
      WSACleanup();
      return;
    }

    if (listen(mysocket, 0x100)) {
      printf("Error listen %d\n",WSAGetLastError());
      closesocket(mysocket);
	  WSACleanup();
      return;
    }
	
	DWORD serverListenID;
	CreateThread(NULL, NULL, serverListenThread, this, NULL, &serverListenID);

	printf("Waiting connections\n");

    
}


void Network::sockClientConnect(char *ip, int _port) {
	char buff[128];
	printf("TCP DEMO CLIENT,%s\n",ip);

    if (WSAStartup(0x202,(WSADATA *)&buff[0]))
    {
      printf("WSAStart error %d\n",WSAGetLastError());
      return;
    }

    
    mysocket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if (mysocket < 0) {
      printf("Socket() error %d\n",WSAGetLastError());
      return;
    }

    sockaddr_in dest_addr;
    dest_addr.sin_family=AF_INET;
    dest_addr.sin_addr.s_addr=inet_addr(ip);
   	dest_addr.sin_port=htons(port);
       
    if (connect(mysocket,(sockaddr *)&dest_addr, sizeof(dest_addr))) {
		printf("Connect error %d\n",WSAGetLastError());
		return;
    }
}

void Network::serverListenSocket() {
	sockaddr_in client_addr;   
	int client_addr_size=sizeof(client_addr);
    // цикл извлечения запросов на подключение из
    // очереди
	SOCKET newSocket;
	while(1) {
		newSocket = accept(mysocket, (sockaddr *)&client_addr, &client_addr_size);
		client_socket.push_back(newSocket);
		std::cout << "New Client Conected\n" << client_socket.size() << "size\n";
	}

}

void Network::closeClientSocket() {
	for (int i=0; i<client_socket.size(); i++)
		closesocket(client_socket.at(i));
	closesocket(mysocket);
}