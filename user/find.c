#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

int find(char *path, const char *filename)
{
	char buf[512], *p;
	int fd;
	struct dirent de;
	struct stat st;
	if((fd = open(path, 0)) < 0)
	{
		fprintf(2, "find: can't open %s\n", path);
		return -1;
	}
	if(fstat(fd, &st) < 0)
	{
		fprintf(2, "find: can't fstat %s\n", path);
		close(fd);
		return -1;
	}
	if(st.type != T_DIR)
	{
		fprintf(2, "find: %s should be dir\n", path);
		close(fd);
		return -1;
	}
	if(strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf))
	{
		fprintf(2, "find: path too long\n");
		close(fd);
		return -1;
	}
	strcpy(buf, path);
	p = buf + strlen(buf);
	*p++ = '/';
	while(read(fd, &de, sizeof(de)) == sizeof(de))
	{
		if(de.inum == 0)
		{
			continue;
		}
		memmove(p, de.name, DIRSIZ);
		p[DIRSIZ] = 0;
		if(stat(buf, &st) < 0)
		{
			fprintf(2, "find: can't stat %s\n", buf);
			continue;
		}
		if(st.type == T_DIR && strcmp(p, ".") && strcmp(p, ".."))
		{
			find(buf, filename);
		}
		else if(!strcmp(p, filename))
		{
			fprintf(1, "%s\n", buf);
		}
	}
	close(fd);
	return 0;
}

int
main(int argc, char *argv[])
{
	if(argc != 3)
	{
		fprintf(2, "find: parameter error\n");
		exit(1);
	}
	if(find(argv[1], argv[2]))
	{
		exit(1);
	}
	exit(0);
}
