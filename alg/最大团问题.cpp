#include <stdio.h>
#include <stdlib.h>
#define N 20
struct code
{
	int a[N][N];
	int n;
	int x[N];
	int bestx[N];
	int cn;
	int bestn;
}Y;
int count;
void Backtrack(int i)
{
	int OK=1;
	int j;
	if(i>Y.n)
	{
		for(j=1;j<=Y.n;j++){
			Y.bestx[j]=Y.x[j];
			
		}
			
		if(Y.bestn<=Y.cn)
		{
			
			for(j=1;j<=Y.n;j++){
		
			printf("结点%d: %d\t",j,Y.bestx[j]);
		}
			Y.bestn=Y.cn;
		}
		printf("\n\n");
		return;
	}
	for(j=1;j<i;j++)
	{
		if(Y.x[j]&&Y.a[i][j]==0)
		{
			OK=0;
			break;
		}
	}
	if(OK)
	{
		Y.x[i]=1;
		Y.cn++;
		Backtrack(i+1);
		Y.x[i]=0;
		Y.cn--;
	}
	if(Y.cn+Y.n
		-i>Y.bestn)
	{
		Y.x[i]=0;
		Backtrack(i+1);
	}
}
int main(void)
{
	int i,j;
	printf("请输入节点个数\n");
	scanf("%d",&count);
	Y.n=count;
	Y.cn=0;
	Y.bestn=0;
	for(i=1;i<=count;i++)
		Y.bestx[i]=0;
	for(i=0;i<=count;i++)
		Y.a[0][i]=0;
	for(i=0;i<=count;i++)
		Y.a[i][0]=0;
	printf("请输入边的关系，存在边为'1',不存在为'0'\n");
	for(i=1;i<=count;i++)
	{
		for(j=1;j<=count;j++)
		{
			printf("a[%d][%d] ",i,j);
			scanf("%d",&Y.a[i][j]);
		}
	}
	for(i=1;i<Y.n;i++)
		Backtrack(i);
	return 0;
}