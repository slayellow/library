#include "CEvent.h"
bool CEvent::Create(EVENT* event, char* name){
	mutex_check = pthread_mutex_init(&event->mutex, 0);
	cond_check = pthread_cond_init(&event->cond, 0);
	event->triggered = false;
	strcpy(event->name, name);
	if (mutex_check == 0 && cond_check == 0){
		eccheck = true;
		return eccheck;
	}else{
		eccheck = false;
		return eccheck;
	}
	return eccheck;
}
void CEvent::Destroy(EVENT* event){
	pthread_mutex_destroy(&event->mutex);
	pthread_cond_destroy(&event->cond);
	eccheck = false;
}
	
bool CEvent::IsCreated(){
	if(eccheck == true){
		return true;
	}else{
		return false;
	}
	return false;
}
bool CEvent::ResetEvent(EVENT* event){
	pthread_mutex_lock(&event->mutex);
	event->triggered = false;
	pthread_mutex_unlock(&event->mutex);
	return true;
}
bool CEvent::SetEvent(EVENT* event){
	pthread_mutex_lock(&event->mutex);
	event->triggered = true;
	pthread_cond_signal(&event->cond);
	pthread_mutex_unlock(&event->mutex);
	return true;
}
bool CEvent::WaitForEvent(EVENT* event){	
	pthread_mutex_lock(&event->mutex);
	while(!event->triggered)
		signalcheck = pthread_cond_wait(&event->cond, &event->mutex);		
	event->triggered = false;
	pthread_mutex_unlock(&event->mutex);
	return true;
}

