/*
【问题描述】
杨辉三角形的打印，请用循环队列实现。

【样例输入】
4

【样例输出】
1
1 1
1 2 1
1 3 3 1
*/

#include <stdio.h>

#define OK  1
#define ERROR  0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 50

typedef struct
{//定义循环队列
	int element[MAXSIZE]; //队列的元素空间
	int front; //头指针
	int rear; //尾指针指示器
}SeqQueue;

void InitQueue(SeqQueue *Q)
{//初始化循环队列
	Q->front=Q->rear=0;
}

int IsEmpty(SeqQueue *Q)
{//判断循环队列是否为空
    if(Q->front==Q->rear)
        return(TRUE);
    else
        return(FALSE);
}

int EnterQueue(SeqQueue *Q,int x)
{//循环队列元素输入
	if((Q->rear+1)%MAXSIZE==Q->front) //队列已经满了
		return(FALSE);
	Q->element[Q->rear]=x;
	Q->rear=(Q->rear+1)%MAXSIZE; //重新设置队尾指针
	return(TRUE);
}

int DeleteQueue(SeqQueue *Q,int *x)
{//删除队列的队头元素，用x返回其值
	if(Q->front==Q->rear) //队列为空
		return(FALSE);
	*x=Q->element[Q->front];
	Q->front=(Q->front+1)%MAXSIZE; //重新设置队头指针
	return(TRUE);
}

int GetHead(SeqQueue *Q,int *x)
{//输出队列的队头元素，用x返回其值
	if(Q->front==Q->rear) //队列为空
		return(FALSE);
	*x=Q->element[Q->front];
	return(TRUE);
}

void YangHuiTriangle(int n)
{//循环队列打印杨辉三角
	int i,j,temp=0,x=0;
	SeqQueue Q;
	InitQueue(&Q);
	EnterQueue(&Q,1); //第一行元素入队
	for(i=2;i<=n;i++)
	{//产生第n行元素并入队，同时打印第n-1行的元素
		EnterQueue(&Q,1); //第n行的第一个元素入队
		for(j=1;j<=i-2;j++)
		{//利用队中第n-1行元素产生第n行的中间n-2个元素并入队
			DeleteQueue(&Q,&temp);
			printf("%d ",temp); //打印第n-1行的元素
			GetHead(&Q,&x);
			temp=temp+x; //利用队中第n-1行元素产生第n行元素
			EnterQueue(&Q,temp); //第n行元素入队
		}
		DeleteQueue(&Q,&x);
		printf("%d ",x); //打印第n-1行的最后一个元素
		printf("\n");
		EnterQueue(&Q,1); //第n行的最后一个元素入队
	}
	while(!IsEmpty(&Q))
    {//打印最后一行元素
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
