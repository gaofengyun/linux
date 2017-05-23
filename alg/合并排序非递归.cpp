#include <stdio.h>
#define N 20

void Merge(int [],int,int,int);
void MergeSort(int [],int);

int main(void)
{
	int s,i,count = 0;
	int a[N];
	printf("Please input numbers,if 0,end\n");
	scanf("%d",&s);
	while(s){
		a[count] = s;
		count++;
		scanf("%d",&s);
	}
	MergeSort(a,count);
	for(i = 0;i < count;i++)
		printf("%5d",a[i]);
	printf("\n");
	return 0;
}


/*合并排序的合并过程*/
void Merge(int a[],int cnt,int num,int end)
{
	int i,j,k,r;
	int b[N];
	i = num;
	j = num + cnt;
	k = 0;
	while(i < num+cnt && j < end)		//两个升序序列合并成一个升序，保证数列有序 
	{
		if(a[i] > a[j]){
			b[k] = a[j];			//定义数组b[N]，存放合并后的升序序列 
			j++;
			k++;
		}		
		else{
			b[k] = a[i];
			k++;
			i++;
		}	
	}
	if(i == num+cnt){			//比较完后必定有一组原升序未遍历完，将未完序列直接赋给b[N] 
		r = j;
		j = end;
	}	
	else{
		r = i;
		j = num+cnt;
	}	
	for(;r<j;r++)	b[k++] = a[r];	
	for(i=0,j=num;i<k;i++,j++)			//将b[N]的值依次赋给原数组，返回释放b[N] 
		a[j] = b[i];
	
}

/*如何分配合并排序数组*/ 
void MergeSort(int a[],int n)
{
	int num = 0,cnt = 1,i,end;
	while(cnt < n)			//满足2的n次方分法，特例6,12等皆可 
	{
		num = 0;
		for(i = num;num < n;num = num + cnt*2)		// 
		{
			if(num+cnt*2<=n)	end = num+cnt*2;	//end 防止数据过界，约束元素 
			else	end = n;
			Merge(a,cnt,num,end);
					//一次性比较两组数据，返回函数跳过两组数据的个数 
		}
		cnt *= 2;
	}	
}



