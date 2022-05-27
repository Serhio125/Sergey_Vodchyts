#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

bool *enabled,fl;
int *file_name_len=NULL;
char **file_content=NULL;
char **file_name=NULL;
long long *file_size=NULL,min_size;
int *file_rights=NULL;
int file_count=0;
char *no1=".",*no2="..",*no3="individ_task.exe",*no4="-kek";
int for_name=0,len_file_count=0;
char *save_file_name=NULL;
FILE *f;

void make_file_name(char* root_dist,char *dir_dist,int j)
{
  int len=1+strlen(root_dist)+strlen(dir_dist)+1+len_file_count+2+(*(file_name_len+j));
  save_file_name=(char*)realloc(save_file_name,len);
  int i,x,shif=strlen(root_dist);
  for (i=0;i<strlen(root_dist);i++)
   save_file_name[i]=root_dist[i];
  for (i=0;i<strlen(dir_dist);i++)
   save_file_name[i+shif]=dir_dist[i];
  i=strlen(dir_dist)+shif;
  save_file_name[i]='/';
  for_name++;
  int len_for_name=0,help=10;
  x=for_name;
  while (help<=x)
    help*=10;
  help/=10;
  while (x!=0)
   {
     x/=10;
     len_for_name++;
   }
  while (len_for_name!=len_file_count)
   {
     len_for_name++; 
     i++;
     save_file_name[i]='0';
   }
  x=for_name;
  while (help!=0)
   {
    i++;
    save_file_name[i]=x/help+'0';
    x%=help;
    help/=10;
   }
  i++;
  save_file_name[i]=')';
  i++;
  save_file_name[i]=' ';
  for (x=0;x<(*(file_name_len+j));x++)
   {
    i++;
    if (file_name[j][x]=='/')
     save_file_name[i]='.'; 
    else  
     save_file_name[i]=file_name[j][x];
   }
  i++;
  save_file_name[i]=0; 
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
    //printf("%s\n",dir_el->d_name);
    if ((strcmp(no1,dir_el->d_name)==0)||(strcmp(no2,dir_el->d_name)==0)||(strcmp(no4,dir_el->d_name)==0)||(strcmp(no4,dir_el->d_name)==0))
     {
       dir_el=readdir(d);
       continue;
     } 
    if (file_count==4)
     x=0; 
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
    {file_count++;
    file_name=(char**)realloc(file_name,file_count*sizeof(char*));
    *(file_name+file_count-1)=NULL;
    file_name_len=(int*)realloc(file_name_len,file_count*sizeof(int));
    file_size=(long long*)realloc(file_size,file_count*sizeof(long long));
    file_rights=(int*)realloc(file_rights,file_count*sizeof(int));
    file_content=(char**)realloc(file_content,file_count*sizeof(char*));
    *(file_content+file_count-1)=NULL;
    x=stat(dist_dir,&buf);
    
    if (x==0)
     {
       *(file_size+file_count-1)=buf.st_size;
       *(file_rights+file_count-1)=buf.st_mode;
       if (dop_slash) 
        {
         *(file_name+file_count-1)=(char*)realloc(*(file_name+file_count-1),sizeof(char)*(strlen(dir_el->d_name))+way_len+1);
         *(file_name_len+file_count-1)=(strlen(dir_el->d_name))+way_len+1;
        }       
       else
        {
          *(file_name+file_count-1)=(char*)realloc(*(file_name+file_count-1),sizeof(char)*(strlen(dir_el->d_name))+way_len);
          *(file_name_len+file_count-1)=(strlen(dir_el->d_name))+way_len;        
        }       
       for (x=0;x<way_len;x++)
        *(*(file_name+file_count-1)+x)=*(way+x);
       if (dop_slash)
        *(*(file_name+file_count-1)+shif-1)='/';
       for (x=0;x<strlen(dir_el->d_name);x++)
        *(*(file_name+file_count-1)+shif+x)=*(dir_el->d_name+x);
       *(file_content+file_count-1)=(char*)realloc(*(file_content+file_count-1),sizeof(char)*(*(file_size+file_count-1)));
       f=fopen(dist_dir,"r");
       if (f!=NULL)
       {
          for (x=0;x<( *(file_size+file_count-1));x++)
           {
             y=fgetc(f);
             *(*(file_content+file_count-1)+x)=(char)y;
           }
         fclose(f);
       }
     }
    }
    dir_el=readdir(d);
  }
  closedir(d);
}

//int argc; char** argv;

int main(int argc,char*argv[])
{
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
   int n=strtol(argv[2],endptr,10);
   if ((*endptr!=(argv[2]+strlen(argv[2])))||(n<1)||(n>2))
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
   get_files(d,argv[1],strlen(argv[1]),true); 
  //printf("Файлы прочитаны вроде как%d\n",file_count);
  fl=true;
  int i;
  //char *right_file_names=NULL;
  /*for (i=0;i<file_count;i++)
   {
    right_file_names=(char*)realloc(right_file_names,*(file_name_len+i)+1);
    for (int l=0;l<*(file_name_len+i);l++)
     *(right_file_names+l)=*(file_name[i]+l);
    *(right_file_names+*(file_name_len+i))=0; 
    //printf("%s - %d\n",right_file_names,(int)*(file_size+i));
   }*/
  i=file_count;
  while (i!=0)
   {
     len_file_count++;
     i/=10;
   }
  enabled=(bool*)malloc(sizeof(bool)*file_count);
  for (i=0;i<file_count;i++)
   enabled[i]=true;
  if (n==1)
   {
     while (fl)
      {
        fl=false;
        for (i=0;i<file_count;i++)
         if (((!fl)||(min_size>file_size[i]))&&(enabled[i]))
          {
            fl=true;
            min_size=file_size[i];
          }
        if (fl)
         {
           for (i=0;i<file_count;i++)
            if (min_size==file_size[i])
             {
               enabled[i]=false;
               make_file_name(argv[1],argv[3],i);
               //printf("%s\n",save_file_name);
               f=NULL;
               f=fopen(save_file_name,"w");
               if (f!=NULL)
                {
                 for (long long q=0;q<file_size[i];q++)
                  fputc(file_content[i][q],f);
                 fclose(f);
                 chmod(save_file_name,file_rights[i]);
                } 
             }
         }
      }
   }
  else
   {
    while (fl)
     {
      fl=false;
      for (i=0;i<file_count;i++)
       if (enabled[i])
        {
          fl=true;
          m=i;
          break;
        }
      if (fl)
       {
        for (i=0;i<file_count;i++)
         if ((strcmp(file_name[m],file_name[i])<0)&&(enabled[i]))
          m=i;
        i=m;
        enabled[i]=false;
         make_file_name(argv[1],argv[3],i);
         f=NULL;
         f=fopen(save_file_name,"w");
         if (f!=NULL)
          {
             for (long long q=0;q<file_size[i];q++)
             fputc(file_content[i][q],f);
             fclose(f);
             chmod(save_file_name,file_rights[i]);
          }
       }
     }
   }
  //closedir(d);
  return 0;
   
}





