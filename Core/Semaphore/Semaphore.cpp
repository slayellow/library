#include "CSemaphore.h"
#include <semaphore.h>

typedef struct {
	sem_t sem;
} __SEM__;

CSemaphor::CSemaphore()
:m_bCreated(false), m_cntMaxKey(0), m_cntCurrentKey(0);
{
	m_hSem = new __SEM__;
}

CSemaphore::~CSemaphore()
{
	Destroy();

	delete m_hSem;
}

bool Create(int a, int b, char *name)
{
	bool bRet = false;
}

void Destroy()
{
	__SEM__ *pSem = (__SEM__ *)m_hSem;

	sem_destroy(&pSem->sem);

	m_bCreated = false;
}

int GetMaxKeyCount()
{
	return m_cntMaxKey;
}

int GetRemainKeyCount()
{
	return m_cntCurrentKey;
}

bool IsCreated()
{
	return m_bCreated;
}

void ReturnSemaphore()
{
	__SEM__ *pSem = (__SEM__ *)m_hSem;

	sem_post(&pSem->sem);
}

void WaitForSemaphore()
{
	__SEM__ *pSem = (__SEM__ *)m_hSem;

	sem_wait(&pSem->sem);
}
