#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "stat.h"
#include "spinlock.h"
#include "proc.h"
#include "fs.h"
#include "sleeplock.h"
#include "file.h"
#include "fcntl.h"
#include "sysinfo.h"

extern uint64 kfreemem(void);
extern int procnum(void);

uint64
sys_sysinfo(void)
{
  struct sysinfo info;
  uint64 p;
  if(argaddr(0, &p) < 0)
    return -1;
  info.freemem = kfreemem();
  info.nproc = procnum();
  if(copyout(myproc()->pagetable, p, (char *)&info, sizeof(info)) < 0)
    return -1;
  return 0;
}

