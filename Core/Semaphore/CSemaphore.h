#include <limits>

class CSemaphore
{
public:
	CSemaphore();
	virtual ~CSemaphore();

	bool Create(int max, char *name);
	void Destroy();

	int GetMaxKeyCount();
	int GetRemainKeyCount();

	bool IsCreated();

	void ReturnSemaphore();
	bool WaitForSemaphore(int secTime);

	int m_cntCurrentKey;	
	
private:
	int m_cntMaxKey;

	char *m_semName;
	bool m_bCreated;
	void* m_hSem;

};
