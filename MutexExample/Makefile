test : CMutex.o CThread.o TestMain.o
	g++ -pthread -o test CMutex.o CThread.o TestMain.o

CMutex.o : CMutex.cpp
	g++ -c -o CMutex.o CMutex.cpp

CThread.o : CThread.cpp
	g++ -c -o CThread.o CThread.cpp

TestMain.o : TestMain.cpp
	g++ -c -o TestMain.o TestMain.cpp

clean :
	rm *.o test
