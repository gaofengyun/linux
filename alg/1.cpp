#include <iostream>  
#define N 30 
int Position(int c[], int len, int i, int X[])  
{  
    int start = 1;  
    int end = len;  
	int mid;
    while (start <= end)  
    {  
       mid = (start + end) / 2;  
        if (X[c[mid]] <X[i])  
        {  
            start = mid + 1;  
        }  
        else  
        {  
            end =  mid - 1;  
        }  
    }  
    return start;  
}  
 
int LongSub(int X[], int n, int c[])  
{  
	int i,len = 1,index; 
    c[0] = -1;  
    c[1] = 0;     
    for (i = 1; i < n; ++i)  
    {  index = Position(c, len, i, X);    
        c[index] = i;  
        if (index >= len)  
        {  
            len = index;  
        }  
    }    
    return len;  
}  
int main()  
{  
    int n,i,max;  
    int X[N];  
    int c[N];  
	printf("输入序列长度\n");
	scanf("%d",&n);
	if(n){printf("输入元素\n");
    for (i = 0; i < n; ++i)  
		scanf("%d",&X[i]);}
	else printf("你的序列长度为零\n");
    max = LongSub(X, n, c);  
   	printf("最长单调递增子序列长度：%d\n",max); 
}  