#include "CFileHigh.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>

CFile::CFile()
 : m_bFile(false), fp(NULL)
{
}

CFile::~CFile()
{
	Destroy();
}

bool CFile::Create(const char* fname, const char* mode)
{
	bool bRet = false;

	if(IsCreated() == false)
	{
		if((fp = fopen(fname, mode)) != NULL)
		{
			bRet = true;
			m_bFile = true;
		}
		else
		{
			perror("Error");
		}
	}
	return bRet;
}

bool CFile::IsCreated()
{
	return m_bFile;
}

int CFile::Write(void* pData, int size)
{
	return fwrite(pData, 1, size, fp);
}

int CFile::Read(void* pData, int size)
{
	return fread(pData, 1, size, fp);
}

int CFile::GetSize()
{
	fseek(fp, 0, SEEK_END);
	return ftell(fp);
}

int CFile::SeekBegin()
{
	return fseek(fp, 0, SEEK_SET);
}

int CFile::SeekEnd()
{
	return fseek(fp, 0, SEEK_END);
}

int CFile::SeekPos(int nPos)
{
	return fseek(fp, nPos, SEEK_SET);
}

void CFile::Destroy()
{
	fclose(fp);
	fp = NULL;
}

