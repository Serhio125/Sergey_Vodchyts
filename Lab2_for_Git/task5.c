#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <unistd.h>

void show_dir(char *dir_dist)
{
  DIR *d=NULL;
  d=opendir(dir_dist);
  if (d==NULL)
   {
    perror("Ошибка при открытии директории");
     return;
   }
  printf("Содержимое каталога %s:",dir_dist);
  struct dirent *dir_el;
  dir_el=readdir(d);
  while (dir_el!=NULL)
   {
     printf("   %s\n",dir_el->d_name);
     dir_el=readdir(d);
   }
  int x=closedir(d);
  if (x!=0)
   {
     perror("Ошибка при закрытии директории");
     return;
   }
 return;
}

int main()
{
 show_dir("./");
 printf("\n");
 show_dir("/");
 return 0;
}
