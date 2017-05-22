#include <stdio.h>  
#include <sys/types.h>  
#include <unistd.h>  
#include <signal.h>  
#include <ctype.h>  
  
#define MAX_CHILD_NUMBER 10  
  
#define SLEEP_INTERVAL 2  
  
int proc_number=0;  
void do_something();  
  
int main(int argc,char *argv[])  
{  
   /* 子进程个数 */  
  int child_proc_number = MAX_CHILD_NUMBER;  
  int i,ch;  
  pid_t child_pid;  
  pid_t pid[10]={0};  
  if(argc>1)/* 命令行参数第一个参数表示子进程个数*/   
  
  {  
      child_proc_number = atoi(argv[1]);  
      child_proc_number = (child_proc_number > 10)?10:child_proc_number;  
  }  
  for(i=0;i<child_proc_number;i++){  
      child_pid = fork();  
      if(child_pid == 0){   
          proc_number = i;  
          do_something();  
      }else{  
       pid[i] = child_pid;  
      }     
  }  
 /* 让用户选择杀死进程，数字表示杀死该进程，q退出 */  
   while((ch=getchar()) != 'q'){  
          if(isdigit(ch)){  
      
             kill(pid[ch-'0'],15);  
       }     
   }     
  /* 在这里填写代码，杀死本组的所有进程 */   
    printf("\n我将要杀死所有的进程\n");   
    sleep(SLEEP_INTERVAL);  
    for(i=0;i<child_proc_number;i++)  
       kill(pid[i],15);  
    return 0;  
}  
  
void do_something(){  
    for(;;){  
        printf("this is process No.%d and its pid is %d\n",proc_number,getpid());  
        sleep(SLEEP_INTERVAL); /* 主动阻塞两秒钟 */  
    }  
}  
