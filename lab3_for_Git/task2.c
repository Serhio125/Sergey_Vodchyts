#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/times.h>
#include <time.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/wait.h>
#include <string.h>

int main(/*int argc,char* argv[]*/)
{
     int m,max_proc;
     int argc=4;
     char *argv[4];
     argv[1]="./";
     argv[2]="delete";
     argv[3]="2";
     DIR *dir_from=NULL,*dir_dist=NULL;
     dir_from=opendir(argv[1]);
     if (argc!=4)
      {
          printf("Ошибка: требуетс ввести 3 передаваемых параметра");
          return 1;
      }
     if (dir_from==NULL)
      {
          perror("Ошибка при открытии директории для чтения"); 
          return 1;
      }
     dir_dist=opendir(argv[2]);
     if (dir_dist==NULL)
      {
         m=mkdir(argv[2],0777);
         if (m!=0)
          {
              perror("Ошибка при создании директории");
              closedir(dir_dist);
              return 1;
          }
      }
     else
      {
          closedir(dir_dist);
      } 
     char **endptr=(char**)malloc(sizeof(char*));
     max_proc=strtol(argv[3],endptr,10);
     if ((*endptr!=(argv[3]+strlen(argv[3])))||(max_proc<1))
      {
          printf("Ошибка: введено некорректное N");
          closedir(dir_dist);
          closedir(dir_from);
          return 1;
      }  
     pid_t pid; 
     int now_proc=0,check_proc; 
     struct dirent *dir_el;
     dir_el=readdir(dir_from);
     while (dir_el!=NULL)
      {
         if (now_proc!=0)
          {
            check_proc=waitpid(-1,NULL,WNOHANG);
            if ((check_proc!=0)&&(check_proc!=-1))
             now_proc--;       
          }
         if (now_proc==max_proc)
          continue; 
         now_proc++;
         pid=fork();
         if (pid==0)
          {
             char *file_check=(char*)malloc(strlen(argv[2])+1+strlen(dir_el->d_name)+1); 
             int x,shif,rights,symb;
             DIR *check_dir=NULL;
             for (x=0;x<strlen(argv[2]);x++)
              file_check[x]=argv[2][x];
             x=strlen(argv[2]);
             shif=x+1;
             file_check[x]='/';
             for (x=0;x<strlen(dir_el->d_name);x++)
              file_check[shif+x]=dir_el->d_name[x];
             x=strlen(dir_el->d_name);
             file_check[shif+x]=0;
             //printf("%s\n",file_check);
             check_dir=opendir(file_check);
             if (check_dir!=NULL)
               return 0;
             FILE *f=NULL;
             f=fopen(file_check,"r");
             if (f!=NULL)
              return 0;
             //fclose(f);
             //f=NULL;
             

             char *file_from=(char*)malloc(strlen(argv[1])+strlen(dir_el->d_name)+1); 
             for (x=0;x<strlen(argv[1]);x++)
              file_from[x]=argv[1][x];
             x=strlen(argv[1]);
             shif=x;
             for (x=0;x<strlen(dir_el->d_name);x++)
              file_from[shif+x]=dir_el->d_name[x];
             x=strlen(dir_el->d_name);
             file_from[shif+x]=0;
             printf("%s\n",file_from);
             check_dir=opendir(file_from);
             if (check_dir!=NULL)
               return 0;
             f=fopen(file_check,"w");  
             //printf("%s\n",file_from);
             struct stat buf;
             stat(file_from,&buf);
             printf("Дочерний процесс, pid - %d, полный путь файла - %s, скопировано байт - %d\n",(int)getpid(),file_from,(int)buf.st_size);
             rights=buf.st_mode;
             FILE *f_from=NULL;
             f_from=fopen(file_from,"r");
             symb=fgetc(f_from);
             while (symb!=EOF)
             {
                 fputc(symb,f);
                 symb=fgetc(f_from);
             }   
             fclose(f);
             fclose(f_from);
             chmod(file_check,rights);
             return 0;
          }
         else
          {
              dir_el=readdir(dir_from);
          } 
      }     
}