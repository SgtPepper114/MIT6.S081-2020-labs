#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
	int sec = 0;
	char *info = "parameter error\n";
	if(argc == 2 && (sec = atoi(argv[1])))
	{
		sleep(sec);
	}
	else
	{
		write(2, info, strlen(info));
		exit(1);
	}
	exit(0);
}
