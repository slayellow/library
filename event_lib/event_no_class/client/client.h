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
#include "sys/ipc.h"
#include "sys/shm.h"
using std::cout;
using std::endl;
#define SERVER_PORT 11235
#define MAXBUF 1024

#include <sys/time.h>

class Client
{
	public:
		Client(EVENT *event);
		~Client();
		void CreateSocket();
		void SendPacket(EVENT *event);

	private:
		EVENT *temp;
		struct sockaddr_in server_addr;
		int client;
		int str_len;	
		int server_len;
		char sendbuf[MAXBUF];
		char recvbuf[MAXBUF];
};
