#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
     pid_t tid;

     tid = syscall(SYS_gettid);
     printf("tid : %d\n",tid);

     tid = syscall(SYS_tkill, 0, 0);
while(1)
{
     printf("tid : %d ...\n",tid);
sleep(1);
}
}
