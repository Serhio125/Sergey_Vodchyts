#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/times.h>
#include <time.h>

int main()
{
     
    pid_t pid1,pid2;
    pid1=fork();
    if (pid1!=0)
     {
        pid2=fork();
        if (pid2==0)
         {
             printf("Второй дочерний процесс, pid - %d, pid родителя - %d\n",getpid(),getppid());
             struct timeval tv2;
             gettimeofday(&tv2,NULL);
             struct tm *real_time2;
             real_time2=localtime(&tv2.tv_sec);
             printf("Время второго дочернего процесса: %d:%d:%d:%d\n",real_time2->tm_hour,real_time2->tm_min,real_time2->tm_sec,(int)((tv2.tv_usec%1000000)/1000));
             while (1)
             {

             }      
         }
        else
         {
             printf("Родительский процесс, pid - %d\n",getpid());
             system("ps -x");
             kill(pid1,15);
             kill(pid2,15);
         } 
     }
    else
     {
        printf("Первый дочерний процесс, pid - %d, pid родителя - %d\n",getpid(),getppid()); 
        struct timeval tv1;
        gettimeofday(&tv1,NULL);
        struct tm *real_time1;
        real_time1=localtime(&tv1.tv_sec);
        printf("Время первого дочернего процесса: %d:%d:%d:%d\n",real_time1->tm_hour,real_time1->tm_min,real_time1->tm_sec,(int)((tv1.tv_usec%1000000)/1000));
        while (1)
             {
                 
             }     
     } 
    return 0; 
}