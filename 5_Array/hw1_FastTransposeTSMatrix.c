/*
【问题描述】
稀疏矩阵的存储不宜用二维数组存储每个元素，那样的话会浪费很多的存储空间。
所以可以使用一个一维数组存储其中的非零元素。这个一维数组的元素类型是一个三元组，由非零元素在该稀疏矩阵中的位置（行号和列号对）以及该元组的值构成。
而矩阵转置就是将矩阵行和列上的元素对换。
请你实现一个快速的对稀疏矩阵进行转置的算法。

【输入形式】
输入的第一行是两个整数r和c（r<200, c<200, r*c <= 12500），分别表示一个包含很多0的稀疏矩阵的行数和列数。接下来有r行，每行有c个整数，用空格隔开，表示这个稀疏矩阵的各个元素。

【输出形式】
输出为读入的稀疏矩阵的转置矩阵。输出共有c行，每行有r个整数，每个整数后输出一个空格。请注意行尾输出换行。

【样例输入】
6 7
0 12 9 0 0 0 0
0 0 0 0 0 0 0
-3 0 0 0 0 14 0
0 0 24 0 0 0 0
0 18 0 0 0 0 0
15 0 0 -7 0 0 0

【样例输出】
0 0 -3 0 0 15
12 0 0 0 18 0
9 0 0 24 0 0
0 0 0 0 0 -7
0 0 0 0 0 0
0 0 14 0 0 0
0 0 0 0 0 0

【提示】
第二组测试数据行列较大。
*/
#include <malloc.h>
#include <stdio.h>

#define MAXSIZE 100000  /*非零元素的个数最多为100000*/

#define ElementType int

/*稀疏矩阵三元组表的类型定义*/
typedef struct
{
	int row,col;  /*该非零元素的行下标和列下标*/
    ElementType e; /*该非零元素的值*/
}Triple;

typedef struct
{
	Triple data[MAXSIZE+1];   /* 非零元素的三元组表。data[0]未用*/
	int m,n,len;          /*矩阵的行数、列数和非零元素的个数*/
}TSMatrix;

void Output(TSMatrix A)
{
    int i,j,k=1;
    for(i=1;i<=A.m;i++)
    {
        for(j=1;j<=A.n;j++)
        {
            if(i!=A.data[k].row || j!=A.data[k].col)
                printf("0 ");
            else
                printf("%d ",A.data[k++].e);
        }
        printf("\n");
    }
}

void FastTransposeTSMatrix(TSMatrix A,TSMatrix *B)
{
	/*基于矩阵的三元组表示，采用"按位快速转置"法，将矩阵A转置为矩阵B*/
	int col,t,p,q;
	int num[MAXSIZE], position[MAXSIZE];
	B->len=A.len;
	B->n=A.m;
	B->m=A.n;
	if(B->len)
	{
		for(col=1;col<=A.n;col++)
			num[col]=0;
		for(t=1;t<=A.len;t++)
			num[A.data[t].col]++; /*计算每一列的非零元素的个数*/
		position[1]=1;
		for(col=2;col<=A.n;col++)  /*求col列中第一个非零元素在B.data[ ]中的正确位置*/
			position[col]=position[col-1]+num[col-1];
		for(p=1;p<=A.len;p++)/*将被转置矩阵的三元组表A从头至尾扫描一次，实现矩阵转置*/
		{
			col=A.data[p].col;
			q=position[col];
			B->data[q].row=A.data[p].col;
			B->data[q].col=A.data[p].row;
			B->data[q].e=A.data[p].e;
			position[col]++;/* position[col]加1，指向下一个列号为col的非零元素在三元组表B中的下标值*/
		}/*end of for*/
	}
}

int main()
{
	int m,n,i,j,x;
	TSMatrix A,B;

	scanf("%d%d",&m,&n);

	A.m = m;
    A.n = n;
    A.len = 0;

	for(i=0;i<m;i++)//读入矩阵
        for(j=0;j<n;j++)
        {
            scanf("%d",&x);
            if(x!=0)
            {
                A.len++;
                A.data[A.len].row = i+1;
                A.data[A.len].col = j+1;
                A.data[A.len].e = x;
            }
        }

	FastTransposeTSMatrix(A,&B);

    Output(B);

	return 0;
}
