#include "CThread.h"

#include <pthread.h>

static void* __ThreadCaller__(void *pParam)
{
	CThread* pThis = (CThread*)pParam;

	pThis->Run();

	return 0;
}

CThread::CThread()
: m_bRun(false), m_Thread(0)
{
}

CThread::~CThread()
{
	ServiceStop();
}

bool CThread::ServiceStart()
{
	bool bRet = false;

	if(IsRun() == false)
	{
		if(pthread_create(&m_Thread, NULL, __ThreadCaller__,this) == 0)
		{
			m_bRun = true;
			bRet = true;
		}
	}

	return bRet;
}

void CThread::ServiceStop()
{
	m_bRun = false;
}

bool CThread::IsRun()
{
	return m_bRun;
}

void CThread::WaitForEndThread()
{
	void* pRet = 0;
	pthread_join(m_Thread, (void **)&pRet);
}

void CThread::Run()
{
}
