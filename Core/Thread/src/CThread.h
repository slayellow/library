/*
 * CThread.h
 *
 *  Created on: 2019. 3. 12.
 *      Author: fm
 */

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
	bool					m_bRun;
	unsigned long int		m_Thread;
};

#endif /* CTHREAD_H_ */
