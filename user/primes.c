#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
	int p_left[2], p_right[2];
	int now, right;
	int flag = 0;
	//初始化
	pipe(p_left);
	now = 2;
	for(int i = 2; i <= 35; i++)
	{
		write(p_left[1], &i, sizeof(int));
	}
	close(p_left[1]);
	//初始化结束
	while(1)
	{
		int num;
		if(!read(p_left[0], &num, sizeof(int)))
		{
			close(p_left[0]);
			close(p_right[1]);
			break;
		}
		if(!(num % now))
		{
			continue;
		}
		if(!flag)
		{
			fprintf(1, "prime %d\n", num);
			right = num;
			pipe(p_right);
			if(!fork())
			{
				now = right;
				p_left[0] = p_right[0];
				p_left[1] = p_right[1];
				close(p_left[1]);
				continue;
			}
			flag = 1;
			close(p_right[0]);
		}
		else
		{
			write(p_right[1], &num, sizeof(int));
		}
	}
	wait(0);
	exit(0);
}
