#include "CEvent.h"
#include <semaphore.h>
#include <time.h>			// clock_gettime
#include <fcntl.h>			// O_CREAT, O_EXCL
#include <math.h>			// INFINITY 
#include <errno.h>			// EEXIST

typedef struct {
	sem_t *sem;
} __EVENT__;


CEvent::CEvent()
: m_bCreated(false), m_cntMax(0), m_cntCurrent(0)
{
	m_pEvent = new __EVENT__;
}

CEvent::~CEvent()
{
	Destroy();

	delete (__EVENT__ *)m_pEvent;
}

bool CEvent::Create(char* name)
{
	bool bRet = false;

	__EVENT__* pEvent = (__EVENT__*)m_pEvent;

	m_eventName = name;

	if((pEvent->sem = sem_open(name, O_CREAT | O_EXCL, 0666, 1)) == SEM_FAILED)
	{
		if (errno == EEXIST)
		{
			pEvent->sem = sem_open(name, 0, 0666, 0);

			bRet = true;

			m_bCreated = true;
		}
	}
	else
	{	
		bRet = true;	

		m_bCreated = true;		
	}

	m_cntMax = 1;

	sem_getvalue(pEvent->sem, &m_cntCurrent);

	return bRet;
}

void CEvent::Destroy()
{
	__EVENT__* pEvent = (__EVENT__*)m_pEvent;

	sem_close(pEvent->sem);

	sem_unlink(m_eventName);

	m_bCreated = false;
}

bool CEvent::IsCreated()
{
	return m_bCreated;
}

void CEvent::ResetEvent()
{
}

void CEvent::SetEvent()
{
	__EVENT__* pEvent = (__EVENT__*)m_pEvent;

	if(m_cntCurrent < m_cntMax)
	{
		sem_post(pEvent->sem);
	}

	sem_getvalue(pEvent->sem, &m_cntCurrent);
}

bool CEvent::WaitForEvent(int secTime)
{
	__EVENT__* pEvent = (__EVENT__*)m_pEvent;

	bool bRet = false;

	timespec _wait;

	clock_gettime(CLOCK_REALTIME, &_wait);

	_wait.tv_sec += (int)secTime;	


	if(sem_timedwait(pEvent->sem, &_wait) == 0)
	{	
		bRet = true;	
	}
	
	sem_getvalue(pEvent->sem, &m_cntCurrent);

	return bRet;
}
