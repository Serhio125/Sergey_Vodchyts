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
#include <sys/stat.h>
#include <dirent.h>
#include <sys/wait.h>


int n,indexx;
char *check=NULL;
char *no1=".",*no2="..",*no3;
bool *status;
char **file_name_shifr=NULL;
char *name=NULL;
pthread_t thread; 
struct timespec ts;
//int argc; char** argv;
char** argvv;
int r=2419,k=157;

short get_shifr(int j)
{
   short z1=k,rez=1,ost=r;
   while (z1!=0)
    {
      while (z1%2==0)
       {
         z1/=2;
         j=(j*j)%ost;
       }
      z1--;
      rez=(rez*j)%r; 
    }
   return rez; 
}

void *for_child(void *p)
{
    int my_index=indexx,l;
    char* file_put=(char*)malloc(1000);
    l=0;
    while (file_name_shifr[my_index][l]!=0)
     {
        file_put[l]=file_name_shifr[my_index][l];
        l++;
     }
    file_put[l]=0;
    char *cop_name=(char*)malloc(strlen(name)+1);
    for (l=0;l<strlen(name);l++)
     cop_name[l]=name[l]; 
    cop_name[strlen(name)]=0; 
    struct stat buf;
    int symbol;
    int x=stat(file_put,&buf);
    unsigned char *file_content=(unsigned char*)malloc(buf.st_size);
    FILE *f;
    f=fopen(file_put,"r");
    for (int i=0;i<buf.st_size;i++)
     {
        symbol=fgetc(f);
        file_content[i]=(unsigned char)symbol;
     }
    fclose(f);
    char *save_name=(char*)malloc(1+strlen(argvv[3])+1+strlen(cop_name));
    for (l=0;l<strlen(argvv[3]);l++)
     save_name[l]=argvv[3][l];
    save_name[l]='/';
    int k=l+1;
    for (l=0;l<strlen(cop_name);l++)
     save_name[k+l]=cop_name[l];
    save_name[k+l]=0; 
    printf("thread - %d, way- %s, bytes- %d\n",(int)pthread_self(),file_put,(int)buf.st_size); 
    f=NULL;
    f=fopen(save_name,"w");
    short shif;
    if (f!=NULL)
     for (int i=0;i<buf.st_size;i++)
      {
        shif=get_shifr(file_content[i]);  
        fputc((*(char*)&shif),f);
        fputc((*(char*)&shif+1),f);
      } 
    fclose(f);     
    status[my_index]=true;
    pthread_exit(NULL);
}

void get_files(DIR *d,char *way,int way_len,bool dop_slash)
{
  char *dist_dir=NULL;
  int x,y,w,shif=0;
  if (dop_slash)
   shif=way_len+1;
  else
   shif=way_len;  
  struct dirent *dir_el;
  dir_el=readdir(d);
  DIR *try_d;
  FILE *f;
  struct stat buf;
  while (dir_el!=NULL)
  { 
    if ((strcmp(no1,dir_el->d_name)==0)||(strcmp(no2,dir_el->d_name)==0)||(strcmp(no3,dir_el->d_name)==0))
     {
       dir_el=readdir(d);
       continue;
     }  
    try_d=NULL;
    if (dop_slash)
     dist_dir=(char*)realloc(dist_dir,1+1+way_len+strlen(dir_el->d_name));
    else
     dist_dir=(char*)realloc(dist_dir,1+way_len+strlen(dir_el->d_name));
    for (x=0;x<way_len;x++)
     dist_dir[x]=way[x];
    if (dop_slash)
     dist_dir[way_len]='/';
    for (x=0;x<strlen(dir_el->d_name);x++)
     dist_dir[shif+x]=dir_el->d_name[x];
    dist_dir[shif+strlen(dir_el->d_name)]=0;     
    try_d=opendir(dist_dir);
    if (try_d!=NULL)
     {  
      get_files(try_d,dist_dir,strlen(dist_dir),true);
     }
    else
    {
       //name=dir_el->d_name;
       bool fl=true;
       int i,j;
       name=(char*)malloc(strlen(dir_el->d_name)+1);
       for (i=0;i<strlen(dir_el->d_name);i++)
        name[i]=dir_el->d_name[i];
       name[strlen(dir_el->d_name)]=0; 
       while (fl)
        for (i=0;i<n;i++)
         if (status[i])
          {
             status[i]=false;
             file_name_shifr[i]=dist_dir;
             fl=false;
             indexx=i;
             break;
          }
       int err=pthread_create(&thread,NULL,for_child,NULL);
       if (err==0)
        {
          ts.tv_sec=0;
          ts.tv_nsec=100000000;
          nanosleep(&ts,NULL);
        }   
       else
        {
            perror("Not today:");
            return;
        }  
    }
    dir_el=readdir(d);
  }
  closedir(d);
}

int main(int argc,char*argv[])
{
   /*
   pthread_t thread; 
   int err=pthread_create(&thread,NULL,for_child,NULL);
   if (err==0)
    {
     struct timespec ts;
     ts.tv_sec=0;
     ts.tv_nsec=100000000;
     nanosleep(&ts,NULL);
     printf("%d\n",check[1]);   
    }   
   else
    {
        perror("Not today:");
        return 0;
    }*/
   /*argc=4;
   argv=(char**)malloc(4*sizeof(char*));
   argv[1]="./";
   argv[2]="1";
   argv[3]="delet";*/
   if (argc!=4)
    {
      printf("Ошибка: требутеся ввести 3 передаваемых параметра\n");
      return 1;
    }
   if (argv[1][strlen(argv[1])-1]!='/')
    {
      printf("Введите имя начального каталога с конечным/\n");
      return 1;
    } 
   DIR *d=NULL;
   d=opendir(argv[1]);
   if (d==NULL)
    {
      perror("Ошибка при открытии каталога");
      return 1;
    }
   char **endptr=(char**)malloc(sizeof(char*));
   n=strtol(argv[2],endptr,10);
   if ((*endptr!=(argv[2]+strlen(argv[2])))||(n<1)||(n>100))
    {
      printf("Ошибка: введено некорректное N\n");
      closedir(d);
      return 1;
    }
   if (argv[3][strlen(argv[3])-1]=='/')
    {
        printf("Введите имя результирующего каталога без конечного/\n");
        closedir(d);
        return 1;
    }  
   int m=mkdir(argv[3],0777);
   if (m!=0)
    {
      perror("Ошибка при создании каталога");
      closedir(d);
      return 1;
    }
   status=(bool*)malloc(n);
   for (int i=0;i<n;i++)
    {
       status[i]=true;
    }
   file_name_shifr=(char**)malloc(n*sizeof(char*)); 
   for (int i=0;i<n;i++)
    {
       file_name_shifr[i]=NULL;
    }
   no3=argv[3];
   argvv=(char**)malloc(sizeof(char*)*argc);
   for (int l=0;l<argc;l++)
    argvv[l]=argv[l];
   get_files(d,argv[1],strlen(argv[1]),true);
   return 0;
}