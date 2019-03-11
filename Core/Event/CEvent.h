
class CEvent
{
public:
	CEvent();
	virtual ~CEvent();

	bool Create(int key);
	void Destroy();

	bool IsCreated();

	void SetEvent();
	void ResetEvent();
	bool WaitForEvent(int msTime);

private:
	bool m_bCreated;

	int m_shmID;
	void* m_pEvent;
};
