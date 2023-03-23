#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
#include "kernel/syscall.h"
#include "kernel/memlayout.h"
#include "kernel/riscv.h"

int 
main(int argc, char *argv[])
{
  char *a;
  int fd, n;

  a = sbrk(PGSIZE);
  fd = open("sbrk", O_CREATE|O_WRONLY);
  unlink("sbrk");
  if(fd < 0)  {
    printf("open sbrk failed\n");
    exit(1);
  }
  if ((n = write(fd, a, PGSIZE)) < 0) {
    printf("write sbrk failed\n");
    exit(1);
  }
  close(fd);

  // test writes to allocated memory
  a = sbrk(PGSIZE);
  if(pipe((int *) a) != 0){
    printf("pipe() failed\n");
    exit(1);
  }
  return 0;
}

