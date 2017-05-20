/*author:Samsons
  date:2015.4.28
  1)����shellָ����ýṹ��洢������ܵ����и���ִ�У�
  2)����strtok_r����ָ������˸��Ӻ�����и
  3)�����˶�ܵ�����
  4)������һЩ�򵥵��쳣���⣬�����ļ�·�����⣬�������⣬ָ�����ȡ�  
  date:2015.4.30  
  �����˺�̨�������&���Ĵ���
  */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX 100
#define LEN 100

//shellָ����ܵ��ṹ��
struct cmd_list{  
    int argc;  //�����ܵ���������
    char *argv[MAX];
};

struct cmd_list *cmdv[MAX];  //shellָ��
int num;//shell�ܵ�����
int flagdo;//�Ƿ�Ϊ��̨����������

//ִ���ⲿ����
void execute(char *argv[])
{
        int error;
        error=execvp(argv[0],argv);
        if (error==-1)  printf("failed!\n");
        exit(1);
}

//�зֵ����ܵ�
void split_cmd(char *line)
{
     struct cmd_list * cmd = (struct cmd_list *)malloc(sizeof(struct cmd_list));
     cmdv[num++] = cmd;
     cmd->argc = 0;
     char *save;
     char *arg = strtok_r(line, " \t", &save);//�зֿո�
     while (arg)
     {
        cmd->argv[cmd->argc] = arg;
        arg = strtok_r(NULL, " \t", &save);
        cmd->argc++;
     }
     cmd->argv[cmd->argc] = NULL;
}

//�зֹܵ�
void split_pipe(char *line)
{
    char *save;
    char * cmd = strtok_r(line, "|", &save);
    while (cmd) {
        split_cmd(cmd);
        cmd = strtok_r(NULL, "|", &save);
    }
}

//ִ�йܵ�����
void do_pipe(int index)
{
    if (index == num - 1)
        execute(cmdv[index]->argv);
    int fd[2];
    pipe(fd);//�����ܵ���0����1д
    if (fork() == 0)
    {
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        execute(cmdv[index]->argv);
    }
    dup2(fd[0], 0);
    close(fd[0]);
    close(fd[1]);
    do_pipe(index + 1);
}

//ִ���ڲ�ָ��
int inner(char *line)
{
    char *save,*tmp[MAX];
    char t[LEN],p[LEN];
    strcpy(t,line);
    char *arg = strtok_r(line, " \t", &save);//�зֿո�
    int i=0;
    while (arg) {
        tmp[i] = arg;
        i++;//��¼�������
        arg = strtok_r(NULL, " \t", &save);
     }
    tmp[i] = NULL;
    if (strcmp(tmp[i-1],"&")==0)//�ж��Ƿ�Ϊ��̨��������
    {
        flagdo=1;
        i--;
    }
    if (strcmp(tmp[0],"exit")==0)//exit
    {
        exit(0);
        return 1;
    }
    else
    if (strcmp(tmp[0],"pwd")==0)//pwd
    {
        char buf[LEN];
        getcwd(buf,sizeof(buf));//�õ���ǰ·��
        printf("Current dir is:%s\n",buf);
        return 1;
    }
    else
    if (strcmp(tmp[0],"cd")==0)//cd
    {
        char buf[LEN];
        if (chdir(tmp[1])>=0)
        {
            getcwd(buf,sizeof(buf));
            printf("Current dir is:%s\n",buf);
        }
        else
        {
            printf("Error path!\n");
        }
        return 1;
    }
    else return 0;
}

//�����ض���
void cat_in(char *q)
{
    char t[30];
    int fd;
    if (q[0]=='<')
    {
        strcpy(t,q+1);
        fd=open(t,O_RDONLY);
        cmdv[0]->argv[cmdv[0]->argc-1]=NULL;  //Ĭ���ض���Ϊ���������һ��
        cmdv[0]->argc--;
        if (fd==-1)
        {
            printf("file open failed\n");
            return;
        }
        dup2(fd,0);
        close(fd);
    }
}

//����ض���
void cat_out(char *q)
{
    char t[30];
    int fd;
    if (q[0]=='>')
    {
        strcpy(t,q+1);
        cmdv[num-1]->argv[cmdv[num-1]->argc-1]=NULL;
        cmdv[num-1]->argc--;
        fd=open(t,O_CREAT|O_RDWR,0666); //0666ΪȨ��
        if (fd==-1)
        {
            printf("file open failed\n");
            return;
        }
        dup2(fd,1);
        close(fd);
    }
}

int main()
{
    int i,pid;
    char buf[LEN],p[LEN];
    while (1)
    {
        fgets(buf,LEN,stdin);//����shellָ��
        if (buf[0]=='\n') continue;
        buf[strlen(buf)-1]='\0';
        strcpy(p,buf);
        int inner_flag;
        inner_flag=inner(buf);//����ָ��ִ��
        if (inner_flag==0)
        {
            pid=fork();//�����µĽ���
            if (pid==0)
            {
                split_pipe(p);//�ܵ����и�
                //����Ǻ�̨�������&����ɾ��
                if (strcmp(cmdv[num-1]->argv[cmdv[num-1]->argc-1],"&")==0)
                {
                    cmdv[num-1]->argc--;
                    cmdv[num-1]->argv[cmdv[num-1]->argc]=NULL;
                }
                //Ĭ����������ض��������һ������������ʱ��һ���ܵ�����������һ���ܵ�
                if (cmdv[0]->argv[cmdv[0]->argc-1]!=NULL)
                {
                    char q[LEN];
                    strcpy(q,cmdv[0]->argv[cmdv[0]->argc-1]);
                    cat_in(q);//�����ض���
                }
                if (cmdv[num-1]->argv[cmdv[num-1]->argc-1]!=NULL)
                {
                    char q[LEN];
                    strcpy(q,cmdv[num-1]->argv[cmdv[num-1]->argc-1]);
                    cat_out(q);//����ض���
                }
                do_pipe(0);//ִ�йܵ�
                exit(0);
            }
            if (flagdo==0)//�Ǻ�̨�������������̲���ȴ��ӽ��̴���
                waitpid(pid,NULL,0);
        }
    }
    return 0;
}