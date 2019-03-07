#include "CEvent.h"
#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

void *thread(void *);
int a=1;
pthread_t tid[1];
EVENT event;
CEvent cv = CEvent();
int main(void){
	cv.Create(&event, "hong");
	int i;
	int id[1];
	for(i=0;i<1;i++){
		id[i] = i;
		pthread_create(&tid[i], NULL, thread, (void*)&id[i]);
	}
	sleep(3);
	cv.SetEvent(&event);
	sleep(3);
	cv.ResetEvent(&event);
	for(i=0; i<1; i++){
		pthread_join(tid[i], NULL);
	}
	cv.Destroy(&event);
	return 0;
}

void *thread(void *arg){
	struct timeval now;
	bool check;
	struct timespec ts;
	for(int i=0;i<2;i++){
		printf("start ThWaitSig..\n");
		gettimeofday(&now, NULL);
		ts.tv_sec = now.tv_sec + 5;
		ts.tv_nsec = now.tv_usec * 1000;
		check = cv.WaitForEvent(&event, ts);	
		if(check == true){		
		std::cout << " what thread num ? " << ((int *)&arg) <<" , a : " << a++ << std::endl;
		}else{
		std::cout << "Event Failed" <<  std::endl;
		}
		
	}
}

