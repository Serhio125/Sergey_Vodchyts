#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/times.h>
#include <time.h>
/*#include <sys/stat.h>
#include <dirent.h>
#include <sys/wait.h>
#include <string.h>*/
#include <sys/time.h>
#include <errno.h>
#include <wait.h>
#include <string.h>
#include <stdbool.h>

pid_t pid1,pid2,pid3,pid4,pid5,pid6,pid7,pid8;
bool fl1=true,fl2=true,fl3=true,fl4=true,fl5=true,fl6=true,fl7=true,fl8=true;
int num=0,send_count=0,first_pid,second_gr;

void to_p1(int sig,siginfo_t *siginfo,void *_)
{
    num++;
    struct timeval tv2;
    gettimeofday(&tv2,NULL);
    struct tm *real_time2;
    real_time2=localtime(&tv2.tv_sec);
    printf("Number - 1 ,pid-%d,ppid-%d, получил SIGUSR2, time:%d:%d:%d:%d\n",getpid(),getppid(),real_time2->tm_hour,real_time2->tm_min,real_time2->tm_sec,(int)((tv2.tv_usec%1000000)/1000));
    if (num==101)
     {
         kill(pid2,SIGTERM);
         waitpid(pid2,NULL,0);
         printf("%d %d завершил работу после %d-ого cигнала SIGUSR2 и %d-ого сигнала SIGUSR1\n",getpid(),getppid(),num,send_count);
         fl1=false;
     }
    else
     {
         send_count++;
         printf("Message number - 1 ,pid-%d,ppid-%d, послал SIGUSR1, time:%d:%d:%d:%d\n",getpid(),getppid(),real_time2->tm_hour,real_time2->tm_min,real_time2->tm_sec,(int)((tv2.tv_usec%1000000)/1000));
         kill(pid2,SIGUSR2);
     } 
}

void to_p2(int sig,siginfo_t *siginfo,void *_)
{
    num++;
    struct timeval tv2;
    gettimeofday(&tv2,NULL);
    struct tm *real_time2;
    real_time2=localtime(&tv2.tv_sec);
    printf("Number - 2 ,pid-%d,ppid-%d, получил SIGUSR2, time:%d:%d:%d:%d\n",getpid(),getppid(),real_time2->tm_hour,real_time2->tm_min,real_time2->tm_sec,(int)((tv2.tv_usec%1000000)/1000));
         send_count+=3;
         printf("Message number - 2 ,pid-%d,ppid-%d, послал SIGUSR1, time:%d:%d:%d:%d\n",getpid(),getppid(),real_time2->tm_hour,real_time2->tm_min,real_time2->tm_sec,(int)((tv2.tv_usec%1000000)/1000));
         /*kill(pid3,SIGUSR1);
         struct timespec ts;
         ts.tv_sec=0;
         ts.tv_nsec=20000000*1;
         nanosleep(&ts,NULL);
         kill(pid4,SIGUSR1);
         //struct timespec ts;
         ts.tv_sec=0;
         ts.tv_nsec=20000000*1;
         nanosleep(&ts,NULL);
         kill(pid5,SIGUSR1);*/
         struct timespec ts;
         ts.tv_sec=0;
         ts.tv_nsec=20000000*1;
         nanosleep(&ts,NULL);
         kill((-1)*pid3,SIGUSR1);
         //kill(0,SIGUSR1);
     
}

void p2_f(int sig,siginfo_t *siginfo,void *_)
{
   kill(pid3,SIGTERM);
   struct timespec ts;
         ts.tv_sec=0;
         ts.tv_nsec=20000000*1;
         nanosleep(&ts,NULL);
   kill(pid4,SIGTERM);
   //struct timespec ts;
         ts.tv_sec=0;
         ts.tv_nsec=20000000*1;
         nanosleep(&ts,NULL);
   kill(pid5,SIGTERM);
   waitpid(pid3,NULL,0);
   waitpid(pid4,NULL,0);
   waitpid(pid5,NULL,0);
   printf("%d %d завершил работу после %d-ого cигнала SIGUSR2 и %d-ого сигнала SIGUSR1\n",getpid(),getppid(),num,send_count);
   fl2=false;
}

void to_p3(int sig,siginfo_t *siginfo,void *_)
{
    if (siginfo->si_pid!=getppid())
     return;
    num++;
    struct timespec ts;
         ts.tv_sec=0;
         ts.tv_nsec=20000000*1;
         nanosleep(&ts,NULL);
    struct timeval tv2;
    gettimeofday(&tv2,NULL);
    struct tm *real_time2;
    real_time2=localtime(&tv2.tv_sec);
    printf("Number - 3 ,pid-%d,ppid-%d, получил SIGUSR1, time:%d:%d:%d:%d\n",getpid(),getppid(),real_time2->tm_hour,real_time2->tm_min,real_time2->tm_sec,(int)((tv2.tv_usec%1000000)/1000));
         send_count++;
         printf("Message number - 3 ,pid-%d,ppid-%d, послал SIGUSR1, time:%d:%d:%d:%d\n",getpid(),getppid(),real_time2->tm_hour,real_time2->tm_min,real_time2->tm_sec,(int)((tv2.tv_usec%1000000)/1000));
         kill(pid7,SIGUSR1);
         //kill(first_pid,SIGUSR2);
}

void p3_f(int sig,siginfo_t *siginfo,void *_)
{
   kill(pid7,SIGTERM);
   waitpid(pid7,NULL,0);
   printf("%d %d завершил работу после %d-ого cигнала SIGUSR1 и %d-ого сигнала SIGUSR2\n",getpid(),getppid(),num,send_count);
   fl3=false;
}

void to_p4(int sig,siginfo_t *siginfo,void *_)
{
    if (siginfo->si_pid!=getppid())
     return;
     struct timespec ts;
         ts.tv_sec=0;
         ts.tv_nsec=20000000*1;
         nanosleep(&ts,NULL);
    num++;
    struct timeval tv2;
    gettimeofday(&tv2,NULL);
    struct tm *real_time2;
    real_time2=localtime(&tv2.tv_sec);
    printf("Number - 4 ,pid-%d,ppid-%d, получил SIGUSR1, time:%d:%d:%d:%d\n",getpid(),getppid(),real_time2->tm_hour,real_time2->tm_min,real_time2->tm_sec,(int)((tv2.tv_usec%1000000)/1000));
         send_count++;
         printf("Message number - 4 ,pid-%d,ppid-%d, послал SIGUSR1, time:%d:%d:%d:%d\n",getpid(),getppid(),real_time2->tm_hour,real_time2->tm_min,real_time2->tm_sec,(int)((tv2.tv_usec%1000000)/1000));
         kill(pid6,SIGUSR1);
}

void p4_f(int sig,siginfo_t *siginfo,void *_)
{
   kill(pid6,SIGTERM);
   waitpid(pid6,NULL,0);
   printf("%d %d завершил работу после %d-ого cигнала SIGUSR1 и %d-ого сигнала SIGUSR2\n",getpid(),getppid(),num,send_count);
   fl4=false;
}

void to_p5(int sig,siginfo_t *siginfo,void *_)
{
    if (siginfo->si_pid!=getppid())
     return; 
    num++;
    struct timespec ts;
         ts.tv_sec=0;
         ts.tv_nsec=20000000*1;
         nanosleep(&ts,NULL);
    struct timeval tv2;
    gettimeofday(&tv2,NULL);
    struct tm *real_time2;
    real_time2=localtime(&tv2.tv_sec);
    printf("Number - 5 ,pid-%d,ppid-%d, получил SIGUSR1, time:%d:%d:%d:%d\n",getpid(),getppid(),real_time2->tm_hour,real_time2->tm_min,real_time2->tm_sec,(int)((tv2.tv_usec%1000000)/1000));
         send_count++;
         printf("Message number - 5 ,pid-%d,ppid-%d, послал SIGUSR1, time:%d:%d:%d:%d\n",getpid(),getppid(),real_time2->tm_hour,real_time2->tm_min,real_time2->tm_sec,(int)((tv2.tv_usec%1000000)/1000));
         kill(pid8,SIGUSR1);
    //kill(first_pid,SIGUSR2);     
}

void p5_f(int sig,siginfo_t *siginfo,void *_)
{
   kill(pid8,SIGTERM);
   waitpid(pid8,NULL,0);
   printf("%d %d завершил работу после %d-ого cигнала SIGUSR1 и %d-ого сигнала SIGUSR2\n",getpid(),getppid(),num,send_count);
   fl5=false;
}

void to_p6(int sig,siginfo_t *siginfo,void *_)
{
    if (siginfo->si_pid!=getppid())
     return; 
    num++;
    struct timeval tv2;
    gettimeofday(&tv2,NULL);
    struct tm *real_time2;
    real_time2=localtime(&tv2.tv_sec);
    printf("Number - 6 ,pid-%d,ppid-%d, получил SIGUSR1, time:%d:%d:%d:%d\n",getpid(),getppid(),real_time2->tm_hour,real_time2->tm_min,real_time2->tm_sec,(int)((tv2.tv_usec%1000000)/1000));
}

void p6_f(int sig,siginfo_t *siginfo,void *_)
{
   printf("%d %d завершил работу после %d-ого cигнала SIGUSR1\n",getpid(),getppid(),num);
   fl6=false;
}

void to_p7(int sig,siginfo_t *siginfo,void *_)
{
    if (siginfo->si_pid!=getppid())
     return; 
    num++;
    struct timeval tv2;
    gettimeofday(&tv2,NULL);
    struct tm *real_time2;
    real_time2=localtime(&tv2.tv_sec);
    printf("Number - 7 ,pid-%d,ppid-%d, получил SIGUSR1, time:%d:%d:%d:%d\n",getpid(),getppid(),real_time2->tm_hour,real_time2->tm_min,real_time2->tm_sec,(int)((tv2.tv_usec%1000000)/1000));
}

void p7_f(int sig,siginfo_t *siginfo,void *_)
{
   printf("%d %d завершил работу после %d-ого cигнала SIGUSR1\n",getpid(),getppid(),num);
   fl7=false;
}

void to_p8(int sig,siginfo_t *siginfo,void *_)
{
    if (siginfo->si_pid!=getppid())
     return; 
    num++;
    struct timeval tv2;
    gettimeofday(&tv2,NULL);
    struct tm *real_time2;
    real_time2=localtime(&tv2.tv_sec);
    printf("Number - 8 ,pid-%d,ppid-%d, получил SIGUSR1, time:%d:%d:%d:%d\n",getpid(),getppid(),real_time2->tm_hour,real_time2->tm_min,real_time2->tm_sec,(int)((tv2.tv_usec%1000000)/1000));
         send_count++;
         printf("Message number - 8 ,pid-%d,ppid-%d, послал SIGUSR2, time:%d:%d:%d:%d\n",getpid(),getppid(),real_time2->tm_hour,real_time2->tm_min,real_time2->tm_sec,(int)((tv2.tv_usec%1000000)/1000));
         kill(first_pid,SIGUSR2);
}

void p8_f(int sig,siginfo_t *siginfo,void *_)
{
   printf("%d %d завершил работу после %d-ого cигнала SIGUSR1 и %d-ого сигнала SIGUSR2\n",getpid(),getppid(),num,send_count);
   fl8=false;
}

void proc8()
{
    struct sigaction sa;
    sa.sa_flags=SA_SIGINFO;
    sa.sa_sigaction=to_p8;
    sigaction(SIGUSR1,&sa,NULL);
    sa.sa_sigaction=p8_f;
    sigaction(SIGTERM,&sa,NULL);
    while (fl8);
}

void proc7()
{
    struct sigaction sa;
    sa.sa_flags=SA_SIGINFO;
    sa.sa_sigaction=to_p7;
    sigaction(SIGUSR1,&sa,NULL);
    sa.sa_sigaction=p7_f;
    sigaction(SIGTERM,&sa,NULL);
    while (fl7);
}

void proc6()
{
    struct sigaction sa;
    sa.sa_flags=SA_SIGINFO;
    sa.sa_sigaction=to_p6;
    sigaction(SIGUSR1,&sa,NULL);
    sa.sa_sigaction=p6_f;
    sigaction(SIGTERM,&sa,NULL);
    while (fl6);
}

void proc5()
{
    setpgid(getpid(),second_gr);
    struct sigaction sa;
    sa.sa_flags=SA_SIGINFO;
    sa.sa_sigaction=to_p5;
    sigaction(SIGUSR1,&sa,NULL);
    sa.sa_sigaction=p5_f;
    sigaction(SIGTERM,&sa,NULL);
    pid8=fork();
    if (pid8==0)
     proc8();
    else 
     while (fl5);
}

void proc4()
{
    setpgid(getpid(),second_gr);
    struct sigaction sa;
    sa.sa_flags=SA_SIGINFO;
    sa.sa_sigaction=to_p4;
    sigaction(SIGUSR1,&sa,NULL);
    sa.sa_sigaction=p4_f;
    sigaction(SIGTERM,&sa,NULL);
    pid6=fork();
    if (pid6==0)
     proc6();
    else 
     while (fl4);
}

void proc3()
{
    setpgid(getpid(),getpid());
    struct sigaction sa;
    sa.sa_flags=SA_SIGINFO;
    sa.sa_sigaction=to_p3;
    sigaction(SIGUSR1,&sa,NULL);
    sa.sa_sigaction=p3_f;
    sigaction(SIGTERM,&sa,NULL);
    pid7=fork();
    if (pid7==0)
     proc7();
    else 
     while (fl3);
}

void proc2()
{
    //signal(SIGUSR1,SIG_IGN);
    struct sigaction sa;
    sa.sa_flags=SA_SIGINFO;
    sa.sa_sigaction=to_p2;
    sigaction(SIGUSR2,&sa,NULL);
    sa.sa_sigaction=p2_f;
    sigaction(SIGTERM,&sa,NULL);
    pid3=fork();
    if (pid3==0)
     proc3();
    else
     {
         second_gr=pid3;
         pid4=fork();
         if (pid4==0)
          proc4();
         else
          {
              pid5=fork();
              if (pid5==0)
               proc5();
              else
               while (fl2); 
          } 
     } 
}

void proc1()
{
    first_pid=getpid();
    struct sigaction sa;
    sa.sa_flags=SA_SIGINFO;
    sa.sa_sigaction=to_p1;
    sigaction(SIGUSR2,&sa,NULL);
    pid2=fork();
    if (pid2==0)
     proc2();
    else
     while (fl1);
}

int main()
{
    pid1=fork();
    if (pid1==0)
     proc1();
    else
     {
        sleep(5);
        kill(pid1,SIGUSR2); 
        waitpid(pid1,NULL,0);
     } 
    return 0; 
}
