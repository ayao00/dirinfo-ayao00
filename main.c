#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>

int main(){
  DIR * tester = opendir("testdir");
  if(errno){
    printf("errno #%d: %s", errno, strerror(errno));
  }

  struct dirent * file = readdir(tester);
  printf("Statistics for directory: %s\n", file->d_name);
  file = readdir(tester);
  struct stat current;
  char * dir[50][256];
  char * files[50][256];
  int i = 0;
  int k = 0;
  int size = 0;
  while(file != NULL){
    if(file->d_type == 4){
      strcpy(dir[i],file->d_name);
      i++;
    }else{
      stat(file->d_name,&current);
      size += current.st_size;
      strcpy(files[k], file->d_name);
      k++;
    }
    file = readdir(tester);
  }
  printf("Total Diectory Size: %d\n", size);
  printf("Directories:\n");
  for(int j = 0; j <i; j++){
    printf("\t%s\n", dir[j]);
  }
  printf("Files:\n");
  for(int j = 0; j <k; j++){
    printf("\t%s\n", files[j]);
  }
  return 0;
}
