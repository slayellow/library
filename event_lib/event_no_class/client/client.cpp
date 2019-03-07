#include "client.h"


Client::Client(EVENT* event)
{
	temp = event;
	EVENT_INIT(temp);
	memset(&server_addr, 0x00, sizeof(server_addr));

}
Client::~Client()
{

	close(client);

}
void Client::CreateSocket()
{
	client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (client == -1){
		cout << "Socket Creation Error" << endl;
		exit(1);
	}
	memset(&server_addr, 0x00, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr =  inet_addr("127.0.0.1") ;
	server_len = connect(client, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if (server_len < 0){
		cout << "Connect Failed " << endl;
		exit(1);

	}
}

void Client::SendPacket(EVENT* event)
{

	while(true){
		memset(sendbuf,0x00,sizeof(sendbuf));
		memset(recvbuf, 0x00, sizeof(recvbuf));
		EVENT_RESET(temp);
		//EVENT_WAIT(&temp);		
		fputs("send message : ", stdout);
		fgets(sendbuf, MAXBUF, stdin);		
		
		write(client, sendbuf, strlen(sendbuf));
		
		sleep(2);
		str_len = read(client, recvbuf, MAXBUF);
		cout << " Server : " << recvbuf;	
	}
	EVENT_DESTROY(temp);
}




int main(void){
	// shared memory code start
	int shmid;
	int skey = 5678;
	void *shared_memory = (void *)0;
	EVENT* shared_event;

	shmid = shmget((key_t)skey, sizeof(EVENT), 0666);
	if(shmid == -1){
		cout << "shmget failed" << endl;
		exit(0);
	}
	shared_memory = shmat(shmid, (void *)0, 0);
	if(!shared_memory){
		cout << "shmat fialed" << endl;
		exit(0);
	}
	shared_event = (EVENT *)shared_memory;
	cout<<shared_memory <<endl;
	// shared memory code start
	Client cli = Client(shared_event);
	cli.CreateSocket();
	cli.SendPacket(shared_event);
	return 0;
}	
