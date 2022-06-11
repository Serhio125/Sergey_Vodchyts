#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/times.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>
#include <wait.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>

int num=0;

void *for_child(void *p)
{
   struct timeval tv2;
   gettimeofday(&tv2,NULL);
   struct tm *real_time2;
   real_time2=localtime(&tv2.tv_sec);
   printf("Child , my pid - %d, parent pid - %d, thread - %d, time - %d:%d:%d:%d\n",getpid(),getppid(),(int)pthread_self(),real_time2->tm_hour,real_time2->tm_min,real_time2->tm_sec,(int)((tv2.tv_usec%1000000)/1000));
   pthread_exit(NULL);
   //return NULL;
}

int main()
{
   struct timeval tv2;
   gettimeofday(&tv2,NULL);
   struct tm *real_time2;
   real_time2=localtime(&tv2.tv_sec); 
   printf("Parent, my pid - %d, parent_pid - %d, thread - %d, time - %d:%d:%d:%d\n",getpid(),getppid(),(int)pthread_self(),real_time2->tm_hour,real_time2->tm_min,real_time2->tm_sec,(int)((tv2.tv_usec%1000000)/1000));
   pthread_t thread;
   int err=pthread_create(&thread,NULL,for_child,NULL);
   if (err==0)
    {
     struct timespec ts;
     ts.tv_sec=0;
     ts.tv_nsec=100000000;
     nanosleep(&ts,NULL);   
    }   
   else
    {
        perror("Not today:");
        return 0;
    }
   err=pthread_create(&thread,NULL,for_child,NULL);
   if (err==0)
    {
     struct timespec ts;
     ts.tv_sec=0;
     ts.tv_nsec=100000000;
     nanosleep(&ts,NULL);   
    }   
   else
    {
        perror("Not today:");
        return 0;
    }
   return 0;
}