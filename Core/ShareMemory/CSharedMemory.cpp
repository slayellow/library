#include "CSharedMemory.h"

#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

CSharedMemory::CSharedMemory()
: m_nameShm(NULL), m_fdShm(-1), m_sizeShm(0)
{

}

CSharedMemory::~CSharedMemory()
{
	Destroy();
}

bool CSharedMemory::Create(char* name, unsigned int size)
{
	bool bRet = false;

	m_nameShm = name;

	// m_nameShm의 KEY값을 가지고, 해당 파일이 없으면 생성하고, 모두에게 읽기 쓰기 권한 부여한 공유 메모리 생성
	m_fdShm = shm_open(m_nameShm, O_CREAT | O_RDWR, 0666);

	if(m_fdShm != -1)
	{
		if(ftruncate(m_fdShm, size) != -1)
		{
			m_sizeShm = size;

			m_bufShm = mmap(NULL, m_sizeShm, PROT_READ | PROT_WRITE, MAP_SHARED, m_fdShm, 0);

			if(m_bufShm != MAP_FAILED)
			{
				bRet = true;
			}
		}
	}

	return bRet;
}

void CSharedMemory::Destroy()
{
	munmap(m_bufShm, m_sizeShm);
	shm_unlink(m_nameShm);

	m_nameShm = NULL;
}

bool CSharedMemory::WriteMemory(void* pData, unsigned int size)
{
	bool bRet = false;

	if( m_sizeShm >= size )
	{
		memcpy(m_bufShm, pData, size);

		bRet = true;
	}

	return bRet;
}

bool CSharedMemory::ReadMemory(void* pData, unsigned int size)
{
	bool bRet = false;

	if( m_sizeShm >= size )
	{
		memcpy(pData, m_bufShm, size);

		bRet = true;
	}

	return bRet;
}
