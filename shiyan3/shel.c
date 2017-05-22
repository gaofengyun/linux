#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<pwd.h>
#define N 100
#define M 20

int main(){
int pid,i;
char *p,*ch = " ";
char buf[N];
char path[N],name[M];
char *arr[M];

while(1){
gethostname(name,M);//返回本地主机的标准主机名
getcwd(path,N);//获得当前工作目录
printf("%s:%s~ ", name,path); 
fflush(stdout);//清空缓冲
gets(buf);
/* 函数返回字符串str1中紧接“标记”的部分的指针, 字符串str2是作为标记的分隔符。
如果分隔标记没有找到，函数返回NULL。为了将字符串转换成标记，
第一次调用str1 指向作为标记的分隔符。之后所以的调用str1 都应为NULL*/
p = strtok(buf,ch);
arr[0] = p;
i = 1;
while(1){
p = strtok(NULL,ch);
arr[i] = p;
if(p == NULL)
break;
i++;
}
pid = fork();
if(pid == 0)//子进程
execvp(arr[0], arr);
wait(NULL);
}

}
