#include <stdio.h>
 #include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
        while(1)
{
	printf("pid:%d, ppid:%d, uid:%d, gid:%d\n", getpid(), getppid(), getuid(), getgid());
sleep(10);
syscall(SYS_tkill,getpid(),1);
}
	return 0;
}
