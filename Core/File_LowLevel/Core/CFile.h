#ifndef __CFILE_H_
#define __CFILE_H_

class CFile
{
public:
	CFile();
	virtual ~CFile();

	bool Create(char* fname, char mode);	//file creat
	void Destroy();							//file close

	bool IsCreated();

	int Write(void* pData, int size);		//file write
	int Read(void* pData, int size);		//file read

	int GetSize();							//file size

	int SeekBegin();							//file located set
	int SeekEnd();							//file located end
	int SeekPos(int nPos);					//file located cur

private:
	int		m_fdFile;
};

#endif
