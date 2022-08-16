#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc > 1){
    fprintf(2, "Usage: pingpong\n");
    exit(1);
  }

  int p1[2];
  int p2[2];
  char buf[1];
  int pid;
  int n;
  int status;

  pipe(p1);
  pipe(p2);
  pid = fork();
  if(pid == 0){
    close(p1[1]);
    close(p2[0]);
    n = read(p1[0], buf, 1);
    if(n < 0){
      fprintf(2, "receive failed\n");
    }
    fprintf(1, "%d: received ping\n", getpid());
    write(p2[1], " ", 1);
    close(p1[0]);
    close(p2[1]);
  } else {
    close(p1[0]);
    close(p2[1]);
    write(p1[1], " ", 1);
    n = read(p2[0], buf, 1);
    if(n < 0){
      fprintf(2, "receive failed\n");
    }
    fprintf(1, "%d: received pong\n", getpid());
    close(p1[1]);
    close(p2[0]);
    wait(&status);
  }

  exit(0);

}
