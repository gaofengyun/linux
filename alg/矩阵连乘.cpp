#include <stdio.h>
#include <stdlib.h>
#define N 50
int m[N][N];//m[][]�洢�˷�����
int s[N][N];//s[][]�洢����Ͽ���λ��
int p[N+1];
//����������˵�����ֵ
void MAtrixChain(int n)
{
	int i,j,k,t,r;
	for(i=1;i<=n;i++)
	{	m[i][i]=0;
		s[i][i]=0;
	}
	for(r=2;r<=n;r++)//r ����������˸���
	{
		for(i=1;i<=n-r+1;i++)
		{	j=i+r-1;
			m[i][j]=m[i+1][j]+p[i-1]*p[i]*p[j];
			s[i][j]=i;
			for(k=i+1;k<j;k++)
			{	t=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
				if(t<m[i][j])
				{	m[i][j]=t;
					s[i][j]=k;
				}
			}
}	}	}
//���ݾ���s������ż������
void Traceback(int i,int j,int s[N][N]){
	if(i==j)	
		return;
	Traceback(i,s[i][j],s);
	Traceback(s[i][j]+1,j,s);
	printf("Multipy A%d,%d\n",i,s[i][j]);
	printf("and A%d,%d\n",s[i][j]+1,j);}
int main(void){
	int i,n;
	printf("������������\n");
	scanf("%d",&n);
	for(i=0;i<=n;i++)
		scanf("%d",&p[i]);
    MAtrixChain(n);
	Traceback(1,6,s);
	return 0;}
