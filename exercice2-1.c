#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main (int argc, char *argv[])
{
  if (fork()) {
    if (!fork()) {
      fork();
      write(0,"1",1);
    } else {
      write(0,"2",1);
    }
  } else {
    write(0,"3",1);
  }
  write(0,"4",1);
  return 0;
}
