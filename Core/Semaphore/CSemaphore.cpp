#include "CSemaphore.h"
#include <semaphore.h>		// Semaphore Function
#include <time.h>			// clock_gettime
#include <fcntl.h>			// O_CREAT, O_EXCL
#include <math.h>			// INFINITY 
#include <errno.h>			// EEXIST
#include <math.h>			// INFINITY

CSemaphore::CSemaphore()
	:m_bCreated(false), m_cntMaxKey(0), m_cntCurrentKey(0)
{
}

CSemaphore::~CSemaphore()
{
	Destroy();
}

bool CSemaphore::Create(int max, char *name)
{
	bool bRet = false;

	m_semName = name;

	if ((m_hSem = sem_open(name, O_CREAT | O_EXCL, 0666, max)) == SEM_FAILED)
	{
		if (errno == EEXIST)
		{
			m_hSem = sem_open(name, 0, 0666, 0);

			bRet = true;

			m_bCreated = true;
		}
	}
	else
	{
		bRet = true;

		m_bCreated = true;
	}

	m_cntMaxKey = max;

	sem_getvalue((sem_t *)m_hSem, &m_cntCurrentKey);

	return bRet;
}

void CSemaphore::Destroy()
{
	sem_t *pSem = (sem_t *)m_hSem;

	sem_close(pSem);

	sem_unlink(m_semName);

	m_bCreated = false;
}

int CSemaphore::GetMaxKeyCount()
{
	return m_cntMaxKey;
}

int CSemaphore::GetRemainKeyCount()
{
	return m_cntCurrentKey;
}

bool CSemaphore::IsCreated()
{
	return m_bCreated;
}

void CSemaphore::ReturnSemaphore()
{
	sem_t *pSem = (sem_t *)m_hSem;

	if (GetRemainKeyCount() < GetMaxKeyCount())
	{
		sem_post(pSem);
	}
	sem_getvalue(pSem, &m_cntCurrentKey);
}

bool CSemaphore::WaitForSemaphore(int secTime)
{
	bool bRet = false;	

	sem_t *pSem = (sem_t *)m_hSem;

	timespec _wait;

	clock_gettime(CLOCK_REALTIME, &_wait);

	_wait.tv_sec += secTime;

	if(sem_timedwait(pSem, &_wait) == 0)
	{	
		bRet = true;	
	}

	sem_getvalue(pSem, &m_cntCurrentKey);
	
	return bRet;
}
