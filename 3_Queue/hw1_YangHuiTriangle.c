#include <stdio.h>

#define OK  1
#define ERROR  0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 50

typedef struct
{
	int element[MAXSIZE];  /* ���е�Ԫ�ؿռ�*/
	int front;  /*ͷָ��ָʾ��*/
	int rear;  /*βָ��ָʾ��*/
}SeqQueue;

void InitQueue(SeqQueue *Q)
{
	Q->front=Q->rear=0;
}

int IsEmpty(SeqQueue *Q)
{
    if(Q->front==Q->rear)
        return(TRUE);
    else
        return(FALSE);
}

int EnterQueue(SeqQueue *Q, int x)
{
	if((Q->rear+1)%MAXSIZE==Q->front)  /*�����Ѿ�����*/
		return(FALSE);
	Q->element[Q->rear]=x;
	Q->rear=(Q->rear+1)%MAXSIZE;  /* �������ö�βָ�� */
	return(TRUE);  /*�����ɹ�*/
}

int DeleteQueue(SeqQueue *Q, int *x)
{
	if(Q->front==Q->rear)  /*����Ϊ��*/
		return(FALSE);
	*x=Q->element[Q->front];
	Q->front=(Q->front+1)%MAXSIZE;  /*�������ö�ͷָ��*/
	return(TRUE);  /*�����ɹ�*/
}

int GetHead(SeqQueue *Q, int *x)
{
	if(Q->front==Q->rear)  /*����Ϊ��*/
		return(FALSE);
	*x=Q->element[Q->front];
	return(TRUE);  /*�����ɹ�*/
}

void YangHuiTriangle(int n)
{
	int i,j,temp=0,x=0;
	SeqQueue Q;
	InitQueue(&Q);
	EnterQueue(&Q,1);  /* ��һ��Ԫ�����*/
	for(i=2;i<=n;i++)   /* ������n��Ԫ�ز���ӣ�ͬʱ��ӡ��n-1�е�Ԫ��*/
	{
		EnterQueue(&Q,1);   /* ��n�еĵ�һ��Ԫ�����*/
		for(j=1;j<=i-2;j++)  /* ���ö��е�n-1��Ԫ�ز�����n�е��м�n-2��Ԫ�ز����*/
		{
			DeleteQueue(&Q,&temp);
			printf("%d ",temp);     /* ��ӡ��n-1�е�Ԫ��*/
			GetHead(&Q,&x);
			temp=temp+x;      /*���ö��е�n-1��Ԫ�ز�����n��Ԫ��*/
			EnterQueue(&Q,temp);
		}
		DeleteQueue(&Q,&x);
		printf("%d ",x);    /* ��ӡ��n-1�е����һ��Ԫ��*/
		EnterQueue(&Q,1);   /* ��n�е����һ��Ԫ�����*/
		printf("\n");
	}
	while(!IsEmpty(&Q))
    {
        DeleteQueue(&Q,&x);
        printf("%d ",x);
    }
}

int main()
{
    int n;
    scanf("%d",&n);
    YangHuiTriangle(n);
    return 0;
}
