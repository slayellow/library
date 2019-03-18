#include "Core/CFile.h"

#include <stdio.h>
#include <string.h>

int main()
{
	CFile w;
	CFile r;
	CFile a;
	CFile t;

	w.Create("test.txt", 'w');
	r.Create("test.txt", 'r');
	a.Create("test.txt", 'a');
	t.Create("ttt.txt", 't');

	char buff1[1024] = "Hello world";
	char buff2[1024];
	w.Write(buff1, sizeof(buff1));
	r.SeekBegin();
	r.Read(buff2, sizeof(buff2));
	printf("%s \n", buff2);

	r.SeekPos(5);
	r.Read(buff2, sizeof(buff2));
	printf("%s \n", buff2);

	t.SeekBegin();
	t.Write(buff1, sizeof(buff1));
	t.Read(buff2, sizeof(buff2));
	printf("total file : %s\n", buff2);

	printf("%d \n", w.GetSize());

	w.Destroy();
}
