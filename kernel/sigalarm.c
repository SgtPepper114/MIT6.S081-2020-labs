#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "defs.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_sigalarm(void){
  struct proc *p = myproc();
  if(argint(0, &p->alarm_interval) < 0 ||
    argaddr(1, (uint64 *)&p->alarm_handler) < 0)
	  return -1;
  return 0;
}

uint64
sys_sigreturn(void){
  struct proc *p = myproc();
  memmove(p->trapframe, p->alarm_tf, sizeof(struct trapframe));
  p->alarm_ishandlering = 0;
  return 0;
}
