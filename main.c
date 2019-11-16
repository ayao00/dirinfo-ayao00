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
  char dir[50][256];
  char files[50][256];
  int i = 0;
  int k = 0;
  int size = 0;
  char filepath[256];
  while(file != NULL){
    if(file->d_type == 4){
      strncpy(dir[i],file->d_name,256);
      i++;
    }else{
      strcat(filepath,"testdir");
      strcat(filepath, "/");
      strcat(filepath, file->d_name);
      stat(filepath,&current);
      printf("%s\n", file->d_name);
      printf("%lld\n", current.st_size);
      printf("%o\n", current.st_mode);
      size += current.st_size;
      strncpy(files[k], file->d_name,256);
      k++;
    }
    file = readdir(tester);
  }
  printf("Total Diectory Size: %d Bytes\n", size);
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
