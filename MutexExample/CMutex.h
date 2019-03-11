class CMutex
{
public:
	CMutex();
	virtual ~CMutex();

	bool Create();
	void Destroy();

	bool IsCreated();

	void Lock();
	void UnLock();

private:
	bool m_bCreated;
	void* m_hMutex;

};
