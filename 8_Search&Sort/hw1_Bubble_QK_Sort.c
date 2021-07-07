/*
����������������һ�����ݣ���0��Ϊ����Ľ������ֱ����ð�����򡢿�������ķ�����
������д�С��������򣬸��������Ľ����
��������ʽ��һ�����ݣ���0��Ϊ����Ľ���
�������ʽ�����������Ľ��
���������롿
9 8 4 5 7 2 10 6 0
�����������
2 4 5 6 7 8 9 10
2 4 5 6 7 8 9 10
*/
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int KeyType;

typedef struct
{
	KeyType key;
}RecordType;

void  BubbleSort(RecordType r[], int length )
{/*�Լ�¼����r��ð������lengthΪ����ĳ���*/
	int n,i,j;
	int change;
	RecordType x;
	n=length;
	change=TRUE;
		for ( i=1 ; i<= n-1 && change ;++i )
		{
			change=FALSE;
				for ( j=1 ; j<= n-i ; ++j)
					if (r[j].key > r[j+1].key )
					{
						x= r[j];
						r[j]= r[j+1];
						r[j+1]= x;
						change=TRUE;
					}
		}
} /*  BubbleSort  */

int   QKPass(RecordType r[],int left,int right)
{/*�Լ�¼����r �е�r[left]��r[right]���ֽ���һ�����򣬲��õ���׼��λ�ã�ʹ�������Ľ��������֮��ǰ���ļ�¼�Ĺؼ��־���С�ڣ����ڣ��ڻ�׼��¼*/
	RecordType x;
	int low,high;
	x=r[left];             /* ѡ���׼��¼*/
	low=left;
	high=right;
	while ( low<high )
	{
		while (low< high && r[high].key>=x.key )
			/* high���ҵ�����С��x.key�ļ�¼ */
			high--;
		if ( low <high )
		{
			r[low]= r[high];
			low++;
		}
		/* �ҵ�С��x.key�ļ�¼������н���*/
		while (low<high && r[low].key<x.key  )    /* low�������Ҵ���x.key�ļ�¼ */
			low++;
		if (  low<high  )
		{
			r[high]= r[low];
			high--;
		} /* �ҵ�����x.key�ļ�¼���򽻻�*/
	}
	r[low]=x;                     /*����׼��¼���浽low=high��λ��*/
	return low;                     /*���ػ�׼��¼��λ��*/
} /* QKPass */

void QKSort(RecordType r[],int low, int high )
{/*�Լ�¼����r[low..high]�ÿ��������㷨��������*/
	int pos;
	if(low<high)
	{
		pos=QKPass(r, low, high);  /*����һ�˿������򣬽�����Ԫ��Ϊ�绮�������ӱ�*/
		QKSort(r, low, pos-1);     /*�����ӱ��������*/
		QKSort(r, pos+1, high); /*���Ҳ��ӱ��������*/

	}
}

void Print(RecordType r[],int length)
{
    int i;
    for(i=1;i<=length;++i)
        printf("%d ",r[i].key);
    printf("\n");
}

int main()
{
    int k=1;
    KeyType x;
    RecordType r1[100],r2[100];

    scanf("%d",&x);
    while(x!=0)
    {
        r1[k].key = x;
        r2[k].key = x;
        k++;
        scanf("%d",&x);
    }

    BubbleSort(r1,k-1);
    QKSort(r2,1,k-1);
    Print(r1,k-1);
    Print(r1,k-1);

    return 0;
}
