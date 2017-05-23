#include <stdio.h>
#include <stdlib.h>
#define N 100

int main (void)
{
int m, n;
char a[N];
int i=0,j;
int counter = 0;
printf("请输入两个整数:");
scanf ("%d%d", &n, &m);//输入两个整数
while(1)
{
	if((m>=0 && n<0)|| (m>0 && n<=0))
	{	printf("请重新输入整数！");
		scanf ("%d%d", &n, &m);//输入两个整数
	}
	else
	{	while (m != n)
		{
			if (n > m)
			{
				n = n / 2;
				a[i++]='g';
				counter++;
			}
			else
			{
			n = n * 3;
			a[i++]='f';
			counter++;
			}
		}
		if(counter>100){
			printf("整数n不能变换成整数m！\n");
		}
		else{
			printf ("%d\n", counter);
			for(j=i-1;j>=0;j--)
			{
			printf("%c",a[j]);
			}
			printf("\n");
		}
		break;
	}
}

return 0;
}