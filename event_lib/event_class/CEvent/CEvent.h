#include <pthread.h>
#include "string.h"
#include "time.h"
#include "sys/time.h"

typedef struct{
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	bool triggered;
	char name[100];
} EVENT;

class CEvent{
private:
	int mutex_check, cond_check;
	bool eccheck;
	int signalcheck;
public:
	
	bool Create(EVENT* event, char* name);
	void Destroy(EVENT* event);
	bool IsCreated();
	bool ResetEvent(EVENT* event);
	bool SetEvent(EVENT* event);
	bool WaitForEvent(EVENT* event);
};
