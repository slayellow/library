#include "CSharedMemory.h"

#include <sys/shm.h>	// 공유 메모리 관련 헤더
#include <string.h>
#include <iostream>

CSharedMemory::CSharedMemory()
: m_sizeMem(0), m_shmID(0), m_buffer(0)
{

}

CSharedMemory::~CSharedMemory()
{
	Destroy();
}

bool CSharedMemory::Create(int key, unsigned int size)
{
	bool bRet = false;

	// 1. 넘어온 key값을 가진, 넘어온 addr의 사이즈를 가진, 읽기/쓰기가 가능한 공유 메모리 생성
	// 2. 성공시 공유 메모리의 ID를 리턴하고 실패시 -1이 리턴
	// 3. 해당 key값을 가진 공유 메모리가 존재하면 생성 하지 않고 이미 생성된 공유 메모리의 ID를 반환
	m_shmID = shmget((key_t)key, size, 0666 | IPC_CREAT);

	if(m_shmID != -1)
	{
		// 1. 인자의 공유 메모리의 ID를 가진 공유 메모리 연결
		m_buffer = (char*)shmat(m_shmID, NULL, 0);

		if(m_buffer != (char*)-1 )
		{
			bRet = true;

			m_sizeMem = size;
		}
		else
		{
			Destroy();
		}
	}

	return bRet;
}

void CSharedMemory::Destroy()
{
	shmdt(m_buffer);

	// 1. 인자의 공유 메모리의 ID를 가진 공유 메모리 제거
	if(shmctl(m_shmID, IPC_RMID, 0) == -1)
	{
		std::cout << "제거 실패" << "\n";
	}
	else
	{
		std::cout << "제거 성공" << "\n";
	}
}

bool CSharedMemory::WriteMemory(void* pData, unsigned int size)
{
	bool bRet = false;

	if( m_sizeMem >= size )
	{
		memcpy(m_buffer, pData, size);

		bRet = true;
	}

	return bRet;
}

bool CSharedMemory::ReadMemory(void* pData, unsigned int size)
{
	bool bRet = false;

	if( m_sizeMem >= size )
	{
		memcpy(pData, m_buffer, size);

		bRet = true;
	}

	return bRet;
}
