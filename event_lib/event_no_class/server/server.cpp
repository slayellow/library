#include "server.h"


Server::Server(EVENT* event)
{
	temp = event;
	EVENT_INIT(temp);
	memset(&server_addr, 0x00, sizeof(server_addr));

}
Server::~Server()
{
	
	close(client);

}
void Server::CreateSocket()
{
	server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server == -1){
		cout << "Socket Creation Error" << endl;
		exit(1);
	}
	int opt=1;
    	socklen_t optlen=sizeof(opt);
	setsockopt(server,SOL_SOCKET,SO_REUSEADDR, &opt,optlen);
	memset(&server_addr, 0x00, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr =  htonl(INADDR_ANY) ;
	server_len = bind(server, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if (server_len < 0){
		cout << "Binding Failed " << endl;
		exit(1);

	}
}
void Server::ConnectClient()
{
	cout << "Waiting for client " << endl;

	listen(server, 5);

	cli_size = sizeof(client_addr);
	client = accept(server, (struct sockaddr *)&client_addr, (socklen_t *)&cli_size);
	if(client < 0)
        {
            printf("Server: accept failed.\n");
            exit(0);
	}

	cout << "Connection Established " << client << endl;
	cout << "IP : " << inet_ntoa(client_addr.sin_addr) << " Port : " << ntohs(client_addr.sin_port) << endl;	
}
void Server::SendPacket(EVENT* event)
{

	while(true){
		EVENT_WAIT(temp);
		memset(sendbuf,0x00,sizeof(sendbuf));
		memset(recvbuf, 0x00, sizeof(recvbuf));

		recv(client, recvbuf, sizeof(recvbuf),0);
		cout << " Client : " << recvbuf;
		
		sleep(2);
		strcpy(sendbuf, recvbuf);
		cout << " Server : " << sendbuf;
		send(client, sendbuf, sizeof(recvbuf), 0);	
	}
	EVENT_DESTROY(temp);

}




int main(void){

	// Shared Memory Code Start
	int shmid;
	void *shared_memory = (void *)0;
	int skey = 5678;
	EVENT *shared_event;
	shmid = shmget((key_t)skey, sizeof(EVENT), 0666|IPC_CREAT);
	if(shmid == -1){
		cout << " shmget failed" << endl;
		exit(0);
	}
	shared_memory = shmat(shmid, (void *)0, 0);
	shared_event = (EVENT *)shared_memory;
	cout<<shared_memory<<endl;
	// Shared Memory Code End
	Server serv = Server(shared_event);
	serv.CreateSocket();
	serv.ConnectClient();
	serv.SendPacket(shared_event);
	shmctl(shmid, IPC_RMID, NULL);
	return 0;
}	
