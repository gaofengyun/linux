#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/syslog.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int init_daemon()
{
	int pid;
	int i;
	time_t t;
//	FILE *lockfd;
	time_t now;
        struct tm* timenow;
	signal(SIGTTOU,SIG_IGN); 
	signal(SIGTTIN,SIG_IGN); 
	signal(SIGTSTP,SIG_IGN);
	signal(SIGHUP,SIG_IGN);  

	if(pid=fork())
		exit(EXIT_SUCCESS);
	else if(pid<0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	setsid();
	if(pid=fork())
		exit(EXIT_SUCCESS);
	else if(pid<0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	for(i=0;i<NOFILE;++i)
		close(i);
	
	//chdir("/tmp");
	chdir("/home/daemon.sys");
	umask(0);
	signal(SIGCHLD,SIG_IGN);
        FILE *fp = fopen("daemon.sys", "w");
    	fprintf(fp, "pid :%d\n", getpid());
        time(&now);
        timenow = localtime(&now);
        fputs(asctime(timenow), fp);
        fclose(fp);

       // fclose(fp);
 //       fclose(lockfd);
}

int main(void)
{
//	time_t t;
	init_daemon();

}
