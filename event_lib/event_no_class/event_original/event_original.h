#ifndef __EVENT_H__  
#define __EVENT_H__  
// 윈도우인 경우
#ifdef WIN32  
#include <windows.h>  
#define     EVENT     HANDLE  
// 리눅스인 경우
#else  
#include <pthread.h>  
typedef struct {  
   pthread_mutex_t mutex; // Mutex 선언
   pthread_cond_t cond;  // 조건변수 선언
   bool triggered;  
} mrevent;  
   
#define EVENT     mrevent 

#endif     
// 함수   
void EVENT_INIT(EVENT *event){  
#ifdef WIN32  
      *event = CreateEvent(NULL, TRUE, FALSE, NULL);  
#else  
      pthread_mutex_init(&event->mutex, 0);  // mutex 객체 초기화
      pthread_cond_init(&event->cond, 0);  // 조건변수 객체 초기화
      event->triggered = false;  
#endif  
}  
   
void EVENT_DESTROY(EVENT *event){  
#ifdef WIN32  
      CloseHandle(*event);  
#else  
      pthread_mutex_destroy(&event->mutex);  // mutex 객체 소멸
      pthread_cond_destroy(&event->cond);  // cond 객체 소멸

#endif  
}  
   
void EVENT_WAIT(EVENT *event){  
#ifdef WIN32  
      WaitForSingleObject(*event, INFINITE);  
#else  
      pthread_mutex_lock(&event->mutex); // critical section start 
      while (!event->triggered)
           pthread_cond_wait(&event->cond, &event->mutex); // 조건변수 cond로 시그널 전달 대기
		//pthread_cond_timedwait(&event->cond, &event->mutex, timeout); // 시간 설정 가능
	
	pthread_mutex_unlock(&event->mutex);  // critical section end
#endif  
}  
   
void EVENT_SET(EVENT *event){  
#ifdef WIN32 
      SetEvent(*event);  // 이벤트 객체를 signal상태로 변환
#else  
   pthread_mutex_lock(&event->mutex); // critical section start
   event->triggered = true;  
   pthread_cond_signal(&event->cond);  // 조건변수 cond에 시그널을 보내 다른 쓰레드 사용
   pthread_mutex_unlock(&event->mutex); // critical section end
#endif  
}  
   
void EVENT_RESET(EVENT *event){  
#ifdef WIN32  
      ResetEvent(*event);  // 이벤트 객체를 non-signal 상태로 변환
#else  
      pthread_mutex_lock(&event->mutex);  // critical section start
      event->triggered = false;  
      pthread_mutex_unlock(&event->mutex);  // critical section end
#endif  
}

  
#endif  
