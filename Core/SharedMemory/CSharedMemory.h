
class CSharedMemory
{
public:
	CSharedMemory();
	virtual ~CSharedMemory();

	bool Create(int key, unsigned int size);				// 공유 메모리 생성
	void Destroy();											// 공유 메모리 제거

	bool ReadMemory(void* pData, unsigned int size);		// 공유 메모리 읽기
	bool WriteMemory(void* pData, unsigned int size);	// 공유 메모리 쓰기

private:
	unsigned int 	m_sizeMem;
	int 			m_shmID;		// 공유 메모리 생성 시 ID
	void* 			m_buffer;
};
