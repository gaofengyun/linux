#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
int main(void)
{
	int fd;
	fd=open("list.txt",0644);
		//fprintf(stderr,"%s","open file error");
	close(0);
	dup(fd);
	close(fd);
	execlp("sort","sort",NULL);
	return 0;
}
