#include <stdio.h>
#include <stdlib.h>
void change(int a[],int b[],int count)
{
	int j,i,t;
	for(i=0;i<count;i++)
	{
		for(j=i+1;j<count;j++)
		{
			if(a[i]>a[j])
			{
				t=a[i];
				a[i]=a[j];
				a[j]=t;
				t=b[i];
				b[i]=b[j];
				b[j]=t;
			}
		}
	}
}
int main(void)
{
	int x,y,n,count=0,k,t;
	int i,j;
	int a[10],b[10];
	printf("输入一个正整数:");
	scanf("%d",&n);
	y=x=n;
	while(x){
		x=x/10;
		count++;
	}
	for(i=count,j=0;i>=0;i--,j++)
	{
		a[j]=y%10;
		b[j]=i;
		y=y/10;
	}
	change(a,b,count);
	printf("输入要删除的位数：");
	scanf("%d",&k);
	k=count-k;
	for(i=0;i<k;i++)
	{
		for(j=i+1;j<k;j++)
		{
			if(b[i]>b[j])
			{
				t=a[i];
				a[i]=a[j];
				a[j]=t;
				t=b[i];
				b[i]=b[j];
				b[j]=t;
			}
		}
	}
	printf("删除后得最小数：");
	for(i=0;i<k;i++)
	{
		printf("%d",a[i]);
	}
	printf("\n");
	return 0;
}