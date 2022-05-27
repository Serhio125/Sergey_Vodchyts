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

bool fl=true;

void my_check(int sig,siginfo_t *siginfo,void *_)
{
   printf("Hello)\n");
   fl=false;
}

int main()
{
    printf("%d %d\n",getpgid(getpid()),getpid());
    /*pid_t pid=fork();
    if (pid==0)
     {
          struct sigaction sa;
          sa.sa_flags=SA_SIGINFO;
          sa.sa_sigaction=my_check;
          sigaction(SIGUSR1,&sa,NULL);
          setpgid(getpid(),getpid());
          printf("Son - %d\n",getpgid(getpid()));
          pid=fork();
          if (pid==0)
           {
               sa.sa_flags=SA_SIGINFO;
               sa.sa_sigaction=my_check;
               sigaction(SIGUSR1,&sa,NULL);
              while (fl);
           }
          else 
           while (fl);
     }     
    else
     {
         printf("Father - %d\n",pid);
         sleep(2);
         kill((-1)*pid,SIGUSR1);
     }     */
    struct sigaction sa;
    sa.sa_flags=SA_SIGINFO;
    sa.sa_sigaction=my_check;
    sigaction(SIGUSR1,&sa,NULL);
    sleep(1);
    kill(getpid(),SIGUSR1);
    while (fl); 
    return 0;
}