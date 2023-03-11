#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

#define MAXLEN 512

int main(int argc, const char *argv[]){
	if(argc < 2){
		fprintf(2, "parameter error\n");
		exit(1);
	}
	int i = 0;
	char c, buf[MAXLEN];
        char *p = buf;
	char *args[MAXARG+1] = {0};
	for(i = 0; i < argc-1; i++)
		args[i] = argv[i+1];
	args[i] = buf;
	while(read(0, &c, 1)){
		if(c == ' ' || c == '\t' || c == '\n'){
			if(args[i] == p)
				continue;
			if(p - buf >= MAXLEN){
				fprintf(2, "parameter too long\n");
				exit(1);
			}
			if(i >= MAXARG){
				fprintf(2, "too many parameters\n");
				exit(1);
			}
			*p++ = 0;
			args[++i] = p;
		} else{
			if(p - buf == MAXLEN){
                                fprintf(2, "parameter too long\n");
                                exit(1);
                        }
			*p++ = c;
		}
		if(c == '\n'){
			args[i] = 0;
			if(!fork()){
				exec(argv[1], args);
				fprintf(2, "exec failed\n");
				exit(1);
			}
			p = buf;
			for(int j = argc-1; j < i; j++)
				args[j] = 0;
			i = argc-1;
			args[i] = buf;
			wait(0);
		}
	}
	exit(0);
}
