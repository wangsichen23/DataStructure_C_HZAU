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
