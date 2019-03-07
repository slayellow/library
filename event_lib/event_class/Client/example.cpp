#include <stdio.h>

#include <signal.h>
#include <time.h>
#include <sys/time.h>

 

void my_timer_callback( unsigned long data )

{

    printf( "my_timer_callback called .\n" );

// exit(1);

}

 

 

int main()

{

    struct itimerval set_time_val, get_time_val;



    sigset(SIGALRM, my_timer_callback);//setitimer가 만료 될 때 호출 될 핸들러

    

    /* 초기 1회에 대한 타이머 */

    set_time_val.it_value.tv_sec = 5;//5초 후 타이머 만료

    set_time_val.it_value.tv_usec = 0;

    

    /* 2회 부터의 값에 대한 타이머 (5초마다 SIGALRM 발생)*/

    set_time_val.it_interval.tv_sec = 5; 

    set_time_val.it_interval.tv_usec = 0;



    if(setitimer(ITIMER_REAL, &set_time_val, NULL) == -1)

    {

        perror("Failed to set virtual timer!\n");



    }



while(getitimer(ITIMER_REAL, &get_time_val) != -1)

    {

        printf( "get_time_val.it_value.tv_sec : %d\n", get_time_val.it_value.tv_sec);

if(get_time_val.it_value.tv_sec == 3)//타이머 시작 2초후 

{

// signal(SIGALRM, SIG_IGN); //시작된 타이머를 취소 한다.

printf( "Cancel Timer.......\n" );

}

    

sleep(1);

}

    return 0;

}
