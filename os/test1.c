#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<ctype.h>

#define MAX_CHILD_NUMBER 10
#define SLEEP_INTERVAL 2

int proc_number = 0;
void do_something();

main(int argc,char* argv[]){
	int child_proc_number = MAX_CHILD_NUMBER;
	int i,ch;
	pid_t child_pid;
	pid_t pid[10] = {0};
	if(argv > 1){
		child_proc_number = atoi(argv[1]);  //将字符串转换为整数
		child_proc_number = (child_proc_number > 10)?10:child_proc_number;
	}
	for(i=0;i<child_proc_number;i++){
		child_pid = fork();
		if(child_pid >0 ){
			pid[i] = child_pid;
			printf("%d  %d\n",i,pid[i]);
		}
		else if(child_pid == 0){
			proc_number = i;
			printf("调用了 %d something函数:\n",i);
			do_something();
		}
		else{
			perror("fail!");
		}
	}
	while((ch = getchar()) != 'q'){
		if(isdigit(ch)){
			kill(pid[ch-'0'],SIGTERM);
			printf("杀死了 %d \n",pid[ch-'0']);
		}
	}

	kill(0,SIGTERM);
	//exit(0);
	return;
}

void do_something(){
//	for(;;){
		printf("This is process No.%d and its pid is %d\n",proc_number,getpid());
		sleep(SLEEP_INTERVAL);
//	}
}  
