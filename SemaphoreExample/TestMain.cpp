#include "Core/Thread/CThread.h"
#include "Core/Mutex/Mutex.h"

#include <stdio.h>
#include <memory.h>
#include <unistd.h>

class CTestThread : public CThread
{
public :
	CTestThread(CMutex* mu)
	{
		pMutex = mu;

	}

	virtual void Run()
	{
		int cnt = 0;
		while( IsRun() )
		{
			Lock(pMutex);

			cnt++;

			printf("Thread1 Count : %d\n ", cnt);
	
			UnLock(pMutex);

		}

		printf("Exit Thread\n");
	}

	CMutex* pMutex;
};


class CTestThread2 : public CThread
{
public :
	CTestThread2(CMutex* mu)
	{
		pMutex = mu;
	}

	virtual void Run()
	{
		int cnt = 0;

		usleep(2000000);

		while( IsRun() )
		{
			Lock(pMutex);
	
			cnt++;
	
			printf("Thread2 Count : %d \n ", cnt);

			UnLock(pMutex);
		}

		printf("Exit Thread\n");
	}

	CMutex* pMutex;
};

int main()
{
	CMutex mutex;
	mutex.Create();

	CTestThread aa(&mutex);
	CTestThread2 bb(&mutex);

	bb.ServiceStart();
	aa.ServiceStart();
	aa.WaitForEndThread();
	bb.WaitForEndThread();


	return 0;
}
