#include <malloc.h>
#include <stdio.h>

#define MAXSIZE 100000  /*����Ԫ�صĸ������Ϊ100000*/

#define ElementType int

/*ϡ�������Ԫ�������Ͷ���*/
typedef struct
{
	int row,col;  /*�÷���Ԫ�ص����±�����±�*/
    ElementType e; /*�÷���Ԫ�ص�ֵ*/
}Triple;

typedef struct
{
	Triple data[MAXSIZE+1];   /* ����Ԫ�ص���Ԫ���data[0]δ��*/
	int m,n,len;          /*����������������ͷ���Ԫ�صĸ���*/
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
	/*���ھ������Ԫ���ʾ������"��λ����ת��"����������Aת��Ϊ����B*/
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
			num[A.data[t].col]++; /*����ÿһ�еķ���Ԫ�صĸ���*/
		position[1]=1;
		for(col=2;col<=A.n;col++)  /*��col���е�һ������Ԫ����B.data[ ]�е���ȷλ��*/
			position[col]=position[col-1]+num[col-1];
		for(p=1;p<=A.len;p++)/*����ת�þ������Ԫ���A��ͷ��βɨ��һ�Σ�ʵ�־���ת��*/
		{
			col=A.data[p].col;
			q=position[col];
			B->data[q].row=A.data[p].col;
			B->data[q].col=A.data[p].row;
			B->data[q].e=A.data[p].e;
			position[col]++;/* position[col]��1��ָ����һ���к�Ϊcol�ķ���Ԫ������Ԫ���B�е��±�ֵ*/
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

	for(i=0;i<m;i++)//�������
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
