
class CEvent
{
public:
	CEvent();
	virtual ~CEvent();

	bool Create(char* name);
	void Destroy();

	bool IsCreated();

	void SetEvent();
	void ResetEvent();
	bool WaitForEvent(int secTime);

private:
	bool m_bCreated;

	int m_cntMax;
	int m_cntCurrent;

	void* m_pEvent;
	char* m_eventName;
};
