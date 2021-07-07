/*
【问题描述】输入一组数据，以0作为输入的结束，分别采用冒泡排序、快速排序的方法，
对其进行从小到大的排序，给出排序后的结果。
【输入形式】一组数据，以0作为输入的结束
【输出形式】两种排序后的结果
【样例输入】
9 8 4 5 7 2 10 6 0
【样例输出】
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
{/*对记录数组r做冒泡排序，length为数组的长度*/
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
{/*对记录数组r 中的r[left]至r[right]部分进行一趟排序，并得到基准的位置，使得排序后的结果满足其之后（前）的记录的关键字均不小于（大于）于基准记录*/
	RecordType x;
	int low,high;
	x=r[left];             /* 选择基准记录*/
	low=left;
	high=right;
	while ( low<high )
	{
		while (low< high && r[high].key>=x.key )
			/* high从右到左找小于x.key的记录 */
			high--;
		if ( low <high )
		{
			r[low]= r[high];
			low++;
		}
		/* 找到小于x.key的记录，则进行交换*/
		while (low<high && r[low].key<x.key  )    /* low从左到右找大于x.key的记录 */
			low++;
		if (  low<high  )
		{
			r[high]= r[low];
			high--;
		} /* 找到大于x.key的记录，则交换*/
	}
	r[low]=x;                     /*将基准记录保存到low=high的位置*/
	return low;                     /*返回基准记录的位置*/
} /* QKPass */

void QKSort(RecordType r[],int low, int high )
{/*对记录数组r[low..high]用快速排序算法进行排序*/
	int pos;
	if(low<high)
	{
		pos=QKPass(r, low, high);  /*调用一趟快速排序，将枢轴元素为界划分两个子表*/
		QKSort(r, low, pos-1);     /*对左部子表快速排序*/
		QKSort(r, pos+1, high); /*对右部子表快速排序*/

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
