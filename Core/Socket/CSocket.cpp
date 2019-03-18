#include "CSocket.h"

#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

#include <iostream>

using namespace std;

CSocket::CSocket()
: m_cSockFD(-1), m_aSockFD(-1), m_addrSize(0)
{

}

CSocket::~CSocket()
{
	Destroy();
}

bool CSocket::Create(int sockType, int flag)
{
	bool bRet = false;

    int					m_broadcast = 1;

	if(flag == 0)			// 서버
	{
		m_cSockFD = socket(AF_INET, sockType, 0);	// 생성 성공 시 파일 디스크립터 리턴, 실패 시 -1을 리턴

		if(m_cSockFD != -1)
		{
			//setsockopt(m_cSockFD, SOL_SOCKET, SO_BROADCAST, &m_broadcast, sizeof(m_broadcast));

			cout << "소켓 생성 성공" << "\n";

			bRet = true;
		}
		else
		{
			cout << "소켓 생성 실패" << "\n";
		}
	}
	else if(flag == 1)	// 클라이언트
	{
		m_aSockFD = socket(AF_INET, sockType, 0);	// 생성 성공 시 파일 디스크립터 리턴, 실패 시 -1을 리턴

		if(m_aSockFD != -1)
		{
			//setsockopt(m_aSockFD, SOL_SOCKET, SO_BROADCAST, &m_broadcast, sizeof(m_broadcast));

			cout << "소켓 생성 성공" << "\n";

			bRet = true;
		}
		else
		{
			cout << "소켓 생성 실패" << "\n";
		}
	}

	return bRet;
}

void CSocket::Destroy()
{
	close(m_cSockFD);
	close(m_aSockFD);
	m_cSockFD = -1;
	m_aSockFD = -1;
}

bool CSocket::IsCreated()
{
	bool bRet = false;

	return bRet;
}

bool CSocket::Bind(int port, char* ip)
{
	bool bRet = false;

	memset(&m_sSockAddr, 0, sizeof(m_sSockAddr));

	m_sSockAddr.sin_family 		= AF_INET;
	m_sSockAddr.sin_port 		= htons(port);
	m_sSockAddr.sin_addr.s_addr	= inet_addr(ip);
	//m_sSockAddr.sin_addr.s_addr	= htonl(INADDR_ANY);

	//m_mreq.imr_multiaddr = m_sSockAddr.sin_addr;
	//m_mreq.imr_interface.s_addr = htonl(INADDR_ANY);

	//setsockopt(m_aSockFD, IPPROTO_IP, IP_ADD_MEMBERSHIP, &m_mreq, sizeof(m_mreq));

	//int yes = 1;

	//setsockopt(m_aSockFD, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));

	if(bind(m_cSockFD, (struct sockaddr*)&m_sSockAddr, sizeof(m_sSockAddr)) != -1)
	//if(bind(m_aSockFD, (struct sockaddr*)&m_sSockAddr, sizeof(m_sSockAddr)) != -1)
	{
		cout << "소켓 결속 성공" << "\n";

		bRet = true;
	}
	else
	{
		cout << "소켓 결속 실패" << "\n";
	}

	return bRet;
}

bool CSocket::Listen(int nListen)	// 이미 연결된 소켓(connect()가 성공한 경우 또는 accept()가 리턴된 경우)에는 적용 못함
{
	bool bRet = false;

	if(listen(m_cSockFD, nListen) != -1)
	{
		cout << "소켓 기다림 성공" << "\n";

		bRet = true;
	}
	else
	{
		cout << "소켓 기다림 실패" << "\n";
	}

	return bRet;
}

bool CSocket::Accept()
{
	bool bRet = false;

	unsigned int m_addrSize;
	m_addrSize = sizeof(m_cSockAddr);

	m_cSockFD = accept(m_cSockFD, (struct sockaddr*)&m_cSockAddr, (socklen_t*)&m_addrSize);

	if(m_aSockFD != -1)
	{
		cout << "소켓 연결 수락 성공" << "\n";

		bRet = true;
	}
	else
	{
		cout << "소켓 연결 수락 실패" << "\n";
	}

	return bRet;
}

bool CSocket::Connect(int port, char* ip)
{
	bool bRet = false;

	memset(&m_sSockAddr, 0, sizeof(m_sSockAddr));

	m_sSockAddr.sin_family 		= AF_INET;
	m_sSockAddr.sin_port 		= htons(port);
	m_sSockAddr.sin_addr.s_addr	= inet_addr(ip);


	if(connect(m_cSockFD, (struct sockaddr*)&m_sSockAddr, sizeof(m_sSockAddr)) != -1)
	{
		cout << "소켓 연결 성공" << "\n";

		bRet = true;
	}
	else
	{
		cout << "소켓 연결 실패" << "\n";
	}

	return bRet;
}

int CSocket::Send(void* pData, int size, int flag)
{
	return send(m_cSockFD, pData, size, flag);
}

int CSocket::Recv(void* pData, int size, int flag)
{
	return recv(m_cSockFD, pData, size, flag);
}

int CSocket::SendTo(void* pData, int size, char* dstIP, int dstPort, int flag)
{
	if(flag == 0)
	{
		return sendto(m_cSockFD, pData, size, 0, (struct sockaddr*)&m_cSockAddr, sizeof(m_cSockAddr));
	}
	else if(flag == 1)
	{
			memset(&m_sSockAddr, 0, sizeof(m_sSockAddr));

			m_sSockAddr.sin_family 		= AF_INET;
			m_sSockAddr.sin_port 		= htons(dstPort);
			m_sSockAddr.sin_addr.s_addr	= inet_addr(dstIP);
			//m_sSockAddr.sin_addr.s_addr	= INADDR_BROADCAST;

			//return sendto(m_aSockFD, pData, size, 0, (struct sockaddr*)&m_sSockAddr, sizeof(m_sSockAddr));
			return sendto(m_cSockFD, pData, size, 0, (struct sockaddr*)&m_sSockAddr, sizeof(m_sSockAddr));
	}
	else
	{
		return -1;
	}
}

int CSocket::RecvFrom(void* pData, int size, char* srcIP, int srcPort, int flag)
{
	// 수신 쪽, send의 반대 클리어 하고 리턴 검사 후 아이피 등 채우기

	unsigned int m_addrSize;

	if(flag == 0)
	{
		m_addrSize = sizeof(m_cSockAddr);

		//return recvfrom(m_cSockFD, pData, size, 0, (struct sockaddr*)&m_cSockAddr, &m_addrSize);
		return recvfrom(m_aSockFD, pData, size, 0, (struct sockaddr*)&m_cSockAddr, &m_addrSize);
	}
	else if(flag == 1)
	{
		memset(&m_sSockAddr, 0, sizeof(m_sSockAddr));

		m_sSockAddr.sin_family 		= AF_INET;
		m_sSockAddr.sin_port 		= htons(srcPort);
		m_sSockAddr.sin_addr.s_addr	= inet_addr(srcIP);

		m_addrSize = sizeof(m_sSockAddr);

		return recvfrom(m_aSockFD, pData, size, 0, (struct sockaddr*)&m_sSockAddr, &m_addrSize);
	}
	else
	{
		return -1;
	}
}
