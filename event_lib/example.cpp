#include "event.h"
#include <iostream>
#include <unistd.h>
#include <pthread.h>

void *thread(void *);
int a=1;
pthread_t tid[4];
EVENT event;

int main(void){
	EVENT_INIT(&event);
	int i;
	int id[1];
	for(i=0;i<1;i++){
		id[i] = i;
		pthread_create(&tid[i], NULL, thread, (void*)&id[i]);
	}
	for(i=0; i<1; i++){
		pthread_join(tid[i], NULL);
	}
	EVENT_DESTROY(&event);
	return 0;
}

void *thread(void *arg){
	// EVENT_RESET(&event); // non-signal
	EVENT_SET(&event);	// signal
	EVENT_WAIT(&event);
	std::cout << " what thread num ? " << ((int *)&arg) <<" , a : " << a++ << std::endl;
}

