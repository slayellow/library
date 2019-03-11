#include "CEvent.h"

#include <pthread.h>
#include <sys/time.h>
#include "sys/shm.h"
#include "sys/ipc.h"

#include <stdio.h>

typedef struct {
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	bool triggered;
	int key;
} __EVENT__;


CEvent::CEvent()
: m_bCreated(false)
{
	m_pEvent = new __EVENT__;
}

CEvent::~CEvent()
{
	Destroy();

	delete m_pEvent;
}

bool CEvent::Create(int key)
{
	bool bRet = false;

//	__EVENT__* pEvent = (__EVENT__*)m_pEvent;
//
//	if( pthread_mutex_init(&pEvent->mutex, 0) == 0 )
//	{
//		if( pthread_cond_init(&pEvent->cond, 0) == 0 )
//		{
//			printf("%d\n", pEvent->cond);
//			bRet = true;
//			m_bCreated = true;
//		}
//
//	}

	// 1. 넘어온 key값을 가진, 넘어온 addr의 사이즈를 가진, 읽기/쓰기가 가능한 공유 메모리 생성
	// 2. 성공시 공유 메모리의 ID를 리턴하고 실패시 -1이 리턴
	// 3. 해당 key값을 가진 공유 메모리가 존재하면 생성 하지 않고 이미 생성된 공유 메모리의 ID를 반환
	m_shmID = shmget((key_t)key, sizeof(__EVENT__), 0666 | IPC_CREAT);

	printf("%d\n", m_shmID);


	if(m_shmID != -1)
	{
		// 1. 인자의 공유 메모리의 ID를 가진 공유 메모리 연결
		m_pEvent = (char*)shmat(m_shmID, NULL, 0);

		if(m_pEvent != (char*)-1 )
		{
			__EVENT__* pEvent = (__EVENT__*)m_pEvent;

//			if( pthread_mutex_init(&pEvent->mutex, 0) == 0 )
//			{
//				if( pthread_cond_init(&pEvent->cond, 0) == 0 )
//				{
//					printf("%d\n", pEvent->cond);
//					bRet = true;
//					m_bCreated = true;
//				}
//
//			}

			pEvent->triggered = false;
			pEvent->key = key;
		}
	}

	return bRet;
}
void CEvent::Destroy()
{
	__EVENT__* pEvent = (__EVENT__*)m_pEvent;

	pthread_mutex_destroy(&pEvent->mutex);
	pthread_cond_destroy(&pEvent->cond);

	m_bCreated = false;
}

bool CEvent::IsCreated()
{
	return m_bCreated;
}

void CEvent::ResetEvent()
{
	__EVENT__* pEvent = (__EVENT__*)m_pEvent;

}

void CEvent::SetEvent()
{
	__EVENT__* pEvent = (__EVENT__*)m_pEvent;

	pthread_mutex_lock(&pEvent->mutex);

	pthread_cond_signal(&pEvent->cond);
	printf("AAAAAAAAAA\n");

	pthread_mutex_unlock(&pEvent->mutex);
}

bool CEvent::WaitForEvent(int msTime)
{
	__EVENT__* pEvent = (__EVENT__*)m_pEvent;

	bool bRet = false;

	timespec _wait;
	timeval _now;
	gettimeofday(&_now, 0);
	_wait.tv_sec = _now.tv_sec + 1;
	_wait.tv_nsec = _now.tv_usec * 1000;

	pthread_mutex_lock(&pEvent->mutex);

	printf("BBBBBBBBBB\n");
	if( pthread_cond_timedwait(&pEvent->cond, &pEvent->mutex, &_wait) == 0 )
	{
		bRet = true;
	}

	pthread_mutex_unlock(&pEvent->mutex);

	return bRet;
}
