#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc,char *argv[])
{
  if (argc!=3)
   {
     printf("Ошибка: требутеся ввести 2 передаваемых параметра\n");
     return -1;
   }
  FILE *f,*f1;
  f=fopen(argv[1],"r");
  if (f==NULL)
  {
    perror("Ошибка при открытии файла");
    return -1;
  }
  f1=fopen(argv[2],"w");
  if (f==NULL)
  {
    perror("Ошибка при создании файла");
    fclose(f);
    return -1;
  }
  struct stat buf;
  stat(argv[1],&buf);
  chmod(argv[2],buf.st_mode);
  int c,x; 
  c=fgetc(f);
  while (c!=EOF)
   {
     x=fputc(c,f1);
     if (x==EOF)
      {
        perror("Ошибка: невозможно записать символ в файл");
        break;
      }
     c=fgetc(f);
   }
    
  x=fclose(f);
  if (x==EOF)
   {
     perror("Ошибка закрытия файла");
     fclose(f1);
     return -1;
   }
  x=fclose(f1);
  if (x==EOF)
   {
     perror("Ошибка закрытия файла");
     return -1;
   }
 printf("\n");
 return 0;
}
