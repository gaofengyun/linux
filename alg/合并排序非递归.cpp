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


/*�ϲ�����ĺϲ�����*/
void Merge(int a[],int cnt,int num,int end)
{
	int i,j,k,r;
	int b[N];
	i = num;
	j = num + cnt;
	k = 0;
	while(i < num+cnt && j < end)		//�����������кϲ���һ�����򣬱�֤�������� 
	{
		if(a[i] > a[j]){
			b[k] = a[j];			//��������b[N]����źϲ������������ 
			j++;
			k++;
		}		
		else{
			b[k] = a[i];
			k++;
			i++;
		}	
	}
	if(i == num+cnt){			//�Ƚ����ض���һ��ԭ����δ�����꣬��δ������ֱ�Ӹ���b[N] 
		r = j;
		j = end;
	}	
	else{
		r = i;
		j = num+cnt;
	}	
	for(;r<j;r++)	b[k++] = a[r];	
	for(i=0,j=num;i<k;i++,j++)			//��b[N]��ֵ���θ���ԭ���飬�����ͷ�b[N] 
		a[j] = b[i];
	
}

/*��η���ϲ���������*/ 
void MergeSort(int a[],int n)
{
	int num = 0,cnt = 1,i,end;
	while(cnt < n)			//����2��n�η��ַ�������6,12�ȽԿ� 
	{
		num = 0;
		for(i = num;num < n;num = num + cnt*2)		// 
		{
			if(num+cnt*2<=n)	end = num+cnt*2;	//end ��ֹ���ݹ��磬Լ��Ԫ�� 
			else	end = n;
			Merge(a,cnt,num,end);
					//һ���ԱȽ��������ݣ����غ��������������ݵĸ��� 
		}
		cnt *= 2;
	}	
}



