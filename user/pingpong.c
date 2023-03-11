#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
	int f2s[2], s2f[2];
	char buf[10];
	pipe(f2s);
	pipe(s2f);
	if(fork())
	{
		close(f2s[0]);
		close(s2f[1]);
		write(f2s[1], "satori", 1);
		close(f2s[1]);
		wait((int *)0);
		if(!read(s2f[0], buf, 1))
		{
			fprintf(2, "error!\n");
			exit(1);
		}
		close(s2f[0]);
		fprintf(1, "%d: received pong\n", getpid());
	}
	else
	{
		close(f2s[1]);
		close(s2f[0]);
		if(!read(f2s[0], buf, 1))
		{
			fprintf(2, "error!\n");
			exit(1);
		}
		close(f2s[0]);
		fprintf(1, "%d: received ping\n", getpid());
		write(s2f[1], "koishi", 1);
		close(s2f[1]);
	}
	exit(0);
}
