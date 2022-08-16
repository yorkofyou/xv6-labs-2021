#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"
#define MAXLEN 100

int
main(int argv, char *argc[]){
  
  char args[MAXARG][MAXLEN];
  char *params[MAXARG];
  char c;
  int index = 0;
  int status;

  for (int i = 0; i < argv; ++i){
    strcpy(args[i], argc[i]);
    params[i] = args[i];
  }

  while(read(0, &c, 1) != 0){
    if(c == '\n'){
      params[argv] = args[argv];
      if(fork() == 0){
        exec(args[1], params+1);
        exit(0);
      }else{
        wait(&status);
      }
      memset(args[argv], 0, MAXLEN);
      index = 0;
    }else{
      args[argv][index++] = c;
    }
  }

  exit(0);
}
