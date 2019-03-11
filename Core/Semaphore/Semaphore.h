class CSemaphore
{
public:
	CSemaphore();
	virtual ~CSemaphore();

	bool Create(int a, int b, char *name);
	void Destroy();

	int GetMaxKeyaCount();
	int GetRemainKeyCount();

	bool IsCreated();

	bool ReturnSemaphore();
	bool WaitForSemaphore();

private:
	int m_cntMaxKey;
	int m_cntCurrentKey;
	
	bool m_bCreated;
	void* m_hSem;

};
