#include <stdio.h>
#include <iostream>
int sort(int a[],int low,int high)
{
	int i,j;
	int x=a[low];
	i=low;
	j=high;
	while(i<j)
	{
		while(i<j&&x<a[j])
			j=j-1;
		if(i<j)
		{
			a[i]=a[j];i++;
		}
		while(i<j&&x>=a[i])
			i++;
		if(i<j)
		{
			a[j]=a[i];
			j--;
		}
	}
	a[i]=x;
	return i;
}
void QuickSort(int a[],int low,int high)
{
	int pos;
	if(low<high)
	{
		pos=sort(a,low,high);
		pos=sort(a,low,pos-1);
		pos=sort(a,pos+1,high);
	}
}
int Sd(int a[],int b[],int s,int e)
{
	int n=0;
	int i=s+1;
	if(a[s]>-1){
		n=1;
		for(;i<=e;i++){
			if(a[i]>=b[s])
				s++;
			else
				n++;
		}
	}
	return n;
}
int main(void)
{
	int n,i;
	int st[20],et[20];
	printf("输入活动数目\n");
	scanf("%d",&n);
	printf("输入：开始时间-结束时间\n");
	for(i=0;i<n;i++)
		scanf("%d%d",&st[i],&et[i]);
	QuickSort(st,0,n-1);
	QuickSort(et,0,n-1);
	printf("至少需要会场：%d\n",Sd(st,et,0,n-1));
	return 0;
}