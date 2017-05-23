#include <stdio.h>
int N;
int D[50][50];
int MaxSum(int r,int j)
{
	int sum1,sum2;
	if(r==N)
		return D[r][j];
	sum1=MaxSum(r+1,j);
	sum2=MaxSum(r+1,j+1);
	if(sum1>sum2)
		return sum1+D[r][j];
	return sum2+D[r][j];
}
int main(void)
{
	int i,j;
	printf("ÊäÈë¾ØÕóĞĞÊı\n");
	scanf("%d",&N);
	for(i=1;i<=N;i++){
		for(j=1;j<=i;j++)
			scanf("%d",&D[i][j]);}
	printf("%d",MaxSum(1,1));
	return 0;
}