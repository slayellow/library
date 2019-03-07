#include "../event_original/event_original.h"
#include <iostream>
#include <string.h>
#include "stdlib.h"
#include "sys/types.h"
#include "netinet/in.h"
#include <fstream>
#include "arpa/inet.h"
#include "unistd.h"
#include "sys/socket.h"
#include "sys/shm.h"
#include "sys/ipc.h"
using std::cout;
using std::endl;
#define SERVER_PORT 11235
#define MAXBUF 1024

#include <sys/time.h>

class Server
{
	public:
		Server(EVENT* event);
		~Server();
		void CreateSocket();
		void ConnectClient();
		void SendPacket(EVENT* event);

	private:
		EVENT *temp;
		int cli_size;
		struct sockaddr_in server_addr, client_addr;
		int server, client;	
		int server_len;
		char sendbuf[MAXBUF];
		char recvbuf[MAXBUF];

};
