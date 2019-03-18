#include "CFile.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>

CFile::CFile()
: m_fdFile(-1)
{
}

CFile::~CFile()
{
	Destroy();
}

bool CFile::Create(char* fname, char mode)
{
	bool bRet = false;

	if(IsCreated() == false)
	{
		switch(mode)
		{
		case 'r':	// read
			m_fdFile = open(fname, O_RDONLY, 0666);
			bRet = true;
			break;
		case 'w':	// write
			m_fdFile = open(fname, O_CREAT | O_WRONLY, 0666);
			bRet = true;
			break;
		case 'a':	// write append
			m_fdFile = open(fname, O_CREAT | O_APPEND | O_WRONLY, 0666);
			bRet = true;
			break;
		case 't':	// read,write
			m_fdFile = open(fname, O_CREAT | O_RDWR, 0666);
			bRet = true;
			break;
		default:
			break;
		}
	}
	return bRet;
}

bool CFile::IsCreated()
{
	return (m_fdFile != -1);
}

int CFile::Write(void* pData, int size)
{
	return write(m_fdFile, pData, size);
}

int CFile::Read(void* pData, int size)
{
	return read(m_fdFile, pData, size);
}

int CFile::GetSize()
{
	struct stat buf;
	fstat(m_fdFile, &buf);

	return buf.st_size;
}

int CFile::SeekBegin()
{
	return lseek(m_fdFile, 0, SEEK_SET);
}

int CFile::SeekEnd()
{
	return lseek(m_fdFile, 0, SEEK_END);
}

int CFile::SeekPos(int nPos)
{
	return lseek(m_fdFile, nPos, SEEK_SET);
}

void CFile::Destroy()
{
	close(m_fdFile);
	m_fdFile = -1;
}

