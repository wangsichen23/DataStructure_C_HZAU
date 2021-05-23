#include<stdio.h>
#include<string.h>
#include<malloc.h>

#define OK  1
#define ERROR  0
#define TRUE 1
#define FALSE 0

#define QueueElementType int
#define MAXSIZE 50

typedef struct Node
{
	QueueElementType data;     /*数据域*/
	struct Node *next;     /*指针域*/
}LinkQueueNode;

typedef struct
{
	LinkQueueNode *front;
	LinkQueueNode *rear;
}LinkQueue;

/*初始化操作。*/
int InitQueue(LinkQueue *Q)
{
	/* 将Q初始化为一个空的链队列 */
	Q->front=(LinkQueueNode *)malloc(sizeof(LinkQueueNode));
	if(Q->front!=NULL)
	{
		Q->rear=Q->front;
		Q->front->next=NULL;
 		return(TRUE);
	}
	else return(FALSE);    /* 溢出！*/
}

/*判断队列是否为空*/
int IsEmpty(LinkQueue *Q)
{
    if(Q->front==Q->rear)
        return(TRUE);
    else
        return(FALSE);
}

/*入队操作。*/
int EnterQueue(LinkQueue *Q, QueueElementType x)
{
	/* 将数据元素x,y插入到队列Q中 */
	LinkQueueNode *NewNode;
	NewNode=(LinkQueueNode * )malloc(sizeof(LinkQueueNode));
	if(NewNode!=NULL)
	{
		NewNode->data=x;
		NewNode->next=NULL;
		Q->rear->next=NewNode;
		Q->rear=NewNode;
		return(TRUE);
	}
	else  return(FALSE);    /* 溢出！*/
}

/*出队操作。*/
int DeleteQueue(LinkQueue *Q)
{
	/* 将队列Q的队头元素出队，并存放到x所指的存储空间中 */
	LinkQueueNode * p;
	int x;
	if(Q->front==Q->rear)
		return(FALSE);
	p=Q->front->next;
	Q->front->next=p->next;  /* 队头元素p出队 */
	if(Q->rear==p)  /* 如果队中只有一个元素p，则p出队后成为空队 */
		Q->rear=Q->front;
	x=p->data;
	free(p);   /* 释放存储空间 */
	return(x);
}

float Queueing(QueueElementType m, QueueElementType total)
{
    LinkQueue P;    //到达时间
    InitQueue(&P);
    LinkQueue Q;    //办理时间
    InitQueue(&Q);
    int R[total];   //结束时间

    int i,k,n,x,y,min,temp;
    float t=0;

    for(i=0;i<total;i++)
    {
        scanf("%d %d",&x,&y);
        EnterQueue(&P,x);
        EnterQueue(&Q,y);
        R[i]=0;
    }

    R[0]=DeleteQueue(&P)+DeleteQueue(&Q);

    while(!IsEmpty(&P))
    {
        k=0;n=0;
        temp=DeleteQueue(&P);
        min=R[0];
        for(i=0;i<m;i++)
            if(R[i]<min)
            {
                min=R[i];
                n=i;
            }
        for(i=0;i<m;i++)
            if(R[i]<=temp)
            {
                R[n]=temp+DeleteQueue(&Q);
                k=1;
                break;
            }
        if(k==1) continue;
        t+=min-temp;
        for(i=0;i<m;i++)
            if(R[i]==min)
            {
                R[i]+=DeleteQueue(&Q);
                break;
            }
    }
    return t;
}

int main()
{
    int m,total;
    float time;
    while(scanf("%d",&m)!=EOF)
    {
        scanf("%d",&total);
        time=Queueing(m,total);
        printf("%.2f\n",time/total);
    }
    return 0;
}
