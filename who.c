#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#define BUFFER_SIZE 1024

int main(int argc,char *argv[])
{
	int fds[2];
	int fd;
//	char buffer[BUFFER_SIZE];
	if(pipe(fds)==-1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	
	if(fork()==0)
	{
		char buf[128];
		dup2(fds[0],0);
		close(fds[1]);
		fd=creat("result.txt",0644);
		dup2(fd,1);
		execlp("sort","sort",(char *)0);

	}
	else
	{
		if(fork()==0)
		{
			dup2(fds[1],1);
			close(fds[0]);
			execlp("who","who",(char *)0);

		}
		else
		{
			close(fds[0]);
			close(fds[1]);
			close(fd);
			wait(NULL);
			wait(NULL);
			//system("cat result.txt");
		}
	}
	
	return 0;
}

