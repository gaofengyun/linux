#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <signal.h>
#include <sys/types.h>
#include <time.h>
#include <syslog.h>

#define MAXFD 64

int main(int argc, char* argv[]){
    
    pid_t pid;
    int i;
    time_t now;
    struct tm* timenow;
    signal(SIGTTOU,SIG_IGN); 
    signal(SIGTTIN,SIG_IGN); 
    signal(SIGTSTP,SIG_IGN);
    signal(SIGHUP,SIG_IGN);  

    if (pid = fork()){
        exit(0);
    }
    else if(pid<0)
    {
		perror("fork");
		exit(EXIT_FAILURE);
    }
    setsid();
    signal(SIGHUP, SIG_IGN);
    if (pid = fork()){
        exit(0);
    }
    else if(pid<0)
    {
		perror("fork");
		exit(EXIT_FAILURE);
    }
  //  daemon_proc = 1;
   // chdir("/tmp");
	 chdir("/Users/Danneels/");
    umask(0);
    for (i = 0; i < MAXFD; i++){
        close(i);
    }
    FILE *fp = fopen("daemon.sys", "w");
    fprintf(fp, "%d", getpid());
    fclose(fp);
    time(&now);
    timenow = localtime(&now);

    fp = fopen("daemon.sys", "a");
    fputs(asctime(timenow), fp);
    fclose(fp);

    return 0;
}
