#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
int main(void)
{
	int filedes;
	if((filedes=open("dd.txt",O_APPEND|O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR))<0)
		fprintf(stderr,"%s ","open file error");
	close(1);
	dup(filedes);
	close(filedes);
	execlp("ls","ls","-l",NULL);
	return 0;
}
