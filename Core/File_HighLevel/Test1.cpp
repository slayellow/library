#include "Core/CFileHigh.h"

#include <stdio.h>
#include <string.h>

int main()
{
	CFile file;
	CFile file1;

	file.Create("test1.txt", "w");

	char buff[1024] = "Hello World";
	char buff1[1024];

	file.Write(buff, sizeof(buff));
	file.Destroy();

	file1.Create("test1.txt", "r");
	file1.SeekBegin();
	file1.Read(buff1, sizeof(buff1));
	printf("%s \n", buff1);

	file1.SeekPos(5);
	file1.Read(buff1, sizeof(buff1));
	printf("%s \n", buff1);

	file1.SeekBegin();
	file1.Read(buff1, sizeof(buff1));
	printf("%s \n", buff1);


	printf("%d \n", file1.GetSize());

	file1.Destroy();
}
