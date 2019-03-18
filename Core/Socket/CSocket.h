#ifndef __CSOCKET_H_
#define __CSOCKET_H_

#include <arpa/inet.h>

class CSocket
{
public:
	CSocket();
	virtual ~CSocket();

    bool Create(int sockType, int flag);  // TCP, UDP
    void Destroy();

    bool IsCreated();

    bool Bind(int port, char* ip = 0);
    bool Listen(int nListen);
    bool Accept();
    bool Connect(int port, char* ip = 0);

    // TCP
    int Send(void* pData, int size, int flag = 0);
    int Recv(void* pData, int size, int flag = 0);

    // UDP
    int SendTo(void* pData, int size, char* dstIP, int dstPort, int flag = 0);
    int RecvFrom(void* pData, int size, char* srcIP, int srcPort, int flag = 0);

private:
    int 					m_cSockFD;		// 소켓 생성 파일 디스크립터
    int					m_aSockFD;		// 소켓 연결 파일 디스크립터
    unsigned int			m_addrSize;	// 소켓 구조체 사이즈
    struct sockaddr_in	m_sSockAddr;	// 서버 소켓 주소 구조체
    struct sockaddr_in	m_cSockAddr;	// 클라이언트 소켓 주소 구조체
    struct ip_mreq		m_mreq;
};

#endif
