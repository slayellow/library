#include "CThread.h"

#include<stdio.h>
#include<unistd.h>

class CTestThread : public CThread
{
public:
	CTestThread()
	{
	}

	virtual void Run()
	{
		int cnt = 0;
		while(IsRun())
		{
			printf("Thread Run  %d \n", cnt);
			cnt++;
			usleep(1000000);
		}
		printf("Exit Thread\n");
	}
};

int main()
{
	CTestThread testThread;


	testThread.ServiceStart();
	testThread.WaitForEndThread();

	return 0;
}
