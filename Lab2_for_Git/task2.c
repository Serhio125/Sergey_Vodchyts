#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(int argc,char *argv[])
{
   if (argc!=2)
    {
       printf("Ошибка: должен передаватся 1 параметр - имя файла");
       return -1;
    }
   FILE *f;
   f=fopen(argv[1],"w");
   if (f==NULL)
    {
      perror("Ошибка: невозможно создать файл для записи");
      return -1;
    }
   int x;
   unsigned char c;
   bool fl=true,fl1=true;
   scanf("%c",&c);
   while ((c!=10)&&(c!=13))
    {
      if (c==6)
       fl=false;
      if (fl)
       {
        x=fputc(c,f);
        if (x==EOF)
         {
           perror("Ошибка записи в файл:");
           fl1=false;
           break;
         }
       }
      scanf("%c",&c);
    }
   if (fl1)
    {
     x=fputc('\n',f);
     if (x==EOF)
       perror("Ошибка записи в файл:");
    }
   x=fclose(f);
   if (x==EOF)
     {
        perror("Ошибка закрытия файла");
        return -1;
     }
   return 0;
}