#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc,char *argv[])
{
  if (argc!=3)
   {
     printf("Ошибка: требутеся ввести 2 передаваемых параметра\n");
     return -1;
   }
  FILE *f;
  f=fopen(argv[1],"r");
  if (f==NULL)
  {
    perror("Ошибка при открытии файла");
    return -1;
  }
  char **endptr=(char**)malloc(sizeof(char*));
  int n=strtol(argv[2],endptr,10);
  if ((*endptr!=(argv[2]+strlen(argv[2])))||(n<0))
   {
     printf("Ошибка: введено некорректное N\n");
     return -1;
   }
  int c=1;
  if (n==0)
    {
     c=fgetc(f);
     while (c!=EOF)
      {
        printf("%c",c);
        c=fgetc(f);
      }
    }
   else
    {
      int i;
      while (c!=EOF)
      {
       for (i=0;i<n;i++)
        {
          c=fgetc(f);
          while ((c!='\n')&&(c!=EOF))
           {
             printf("%c",c);
             c=fgetc(f);
           }
          if (c==EOF)
           break;
          printf("%c",c);
        }
       if (c!=EOF)
        i=getchar();
      }
    }
  int x=fclose(f);
  if (x==EOF)
   {
     perror("Ошибка закрытия файла");
     return -1;
   }
 printf("\n");
 return 0;
}
