#ifndef __CTHREAD_H_
#define __CTHREAD_H_

class CThread
{
public:
    CThread();
    virtual ~CThread();

    bool ServiceStart();
    void ServiceStop();

    bool IsRun();
    void WaitForEndThread();

    virtual void Run();

private:
    bool 					m_bRun;		// Thread State
    unsigned long int 	m_hThread;		// Thread Handle
};

#endif  // __CTHREAD_H_
