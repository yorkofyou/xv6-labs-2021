#include "kernel/types.h"
#include "user/user.h"

void
child(int *pl){
  int pr[2];
  int prime;
  int n;
  int status;


  close(pl[1]);
  close(pr[0]);
  if(read(pl[0], &prime, sizeof(int)) == 0){
    close(pl[0]);
    close(pr[1]);
    exit(0);
  }
  fprintf(1, "prime %d\n", prime);
  pipe(pr);
  if(fork()==0){
    child(pr);
  }else{
    while(read(pl[0], &n, sizeof(int)) != 0){
      if(n%prime!=0){
        write(pr[1], &n, sizeof(int));
      }
    }
    close(pl[0]);
    close(pr[1]);
    wait(&status);
  }
  exit(0);
}

int
main(int argv, char *argc[]){
  
  if(argv != 1){
    fprintf(2, "Usage: primes\n");
    exit(1);
  }
  
  int pl[2];
  int status;

  pipe(pl);
  if(fork() == 0){
    child(pl);
  }else{
    close(pl[0]);
    for(int i = 2; i <= 35; ++i){
      write(pl[1], &i, sizeof(int));
    }
    close(pl[1]);
    wait(&status);
  }
  
  exit(0);

}
