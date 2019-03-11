#include "CMutex.h"
#include <pthread.h>

typedef struct {
	pthread_mutex_t mutex;
} __MUTEX__;



CMutex::CMutex()
: m_bCreated(false)
{
	m_hMutex = new __MUTEX__;

}

CMutex::~CMutex()
{
	Destroy();

	delete m_hMutex;
}

bool CMutex::Create()
{
	bool bRet = false;

	__MUTEX__ * pMutex = (__MUTEX__ *)m_hMutex;

	if( pthread_mutex_init(&pMutex->mutex, 0) == 0)
	{
		bRet = true;
		m_bCreated = true;
	}

	return bRet;
}

void CMutex::Destroy()
{
	__MUTEX__ * pMutex = (__MUTEX__ *)m_hMutex;

	pthread_mutex_destroy(&pMutex->mutex);

	m_bCreated = false;
}

bool CMutex::IsCreated()
{
	return m_bCreated;
}

void CMutex::Lock()
{
	__MUTEX__ * pMutex = (__MUTEX__ *)m_hMutex;
	
	pthread_mutex_lock(&pMutex->mutex);
}

void CMutex::UnLock()
{
	__MUTEX__ * pMutex = (__MUTEX__ *)m_hMutex;

	pthread_mutex_unlock(&pMutex->mutex);
}

