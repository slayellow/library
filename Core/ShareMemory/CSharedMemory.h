#ifndef __CSHAREDMEMORY_H_
#define __CSHAREDMEMORY_H_

class CSharedMemory
{
public:
	CSharedMemory();											// 공유 메모리 생성자
	virtual ~CSharedMemory();								// 공유 메모리 소멸자

	bool Create(char* name, unsigned int size);			// 공유 메모리 생성
	void Destroy();											// 공유 메모리 삭제
 
	bool ReadMemory(void* pData, unsigned int size);		// 공유 메모리 읽기
	bool WriteMemory(void* pData, unsigned int size);	// 공유 메모리 쓰기

private:
	char* 					m_nameShm;							// 공유 메모리 이름

	int 					m_fdShm;							// 공유 메모리 파일 디스크립터
	unsigned int 			m_sizeShm;							// 공유 메모리 사이즈

	void* 					m_bufShm;							// 공유 메모리 버퍼
};

#endif
