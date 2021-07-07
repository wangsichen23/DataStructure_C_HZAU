/*
【问题描述】
每天刚开始时银行会开m个窗口来为我们total个客户办理业务
当有客户需要办理业务时，先选择可以办理业务的窗口
如果有多个窗口可以办理业务就选择空闲时间最长的窗口
如果有多个窗口空闲的时间一样长，则选择序号小的窗口办理业务。
假设我们每个人来到的时间和办理业务所需要的时间都为整数。
现在请你算算我们平均需要等待多久呢？

【输入形式】
有多组测试数据，每组数据开始有两个正整数m(<20)和total(<200)
m: 银行会开放窗口个数
total：客户先后到来的时间以及办理业务所需的时间。

【输出形式】
平均等待的时间，保留两位小数。

【样例输入】
2 6 1 3 4 1 5 3 9 2 13 4 13 3
3 14 0 3 2 2 2 4 5 4 7 2 11 3 12 3 12 4 12 1 13 3 15 4 19 1 22 3 23 2
2 5 0 6 0 5 0 6 7 1 7 2

【样例输出】
0.00
0.29
1.20

【要求】
请用顺序队列或链式队列来完成，否则不得分。
*/

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
{//链队列结点
	QueueElementType data; //数据域
	struct Node *next; //指针域
}LinkQueueNode;

typedef struct
{//定义链队列
	LinkQueueNode *front; //队头指针
	LinkQueueNode *rear; //队尾指针
}LinkQueue;

int InitQueue(LinkQueue *Q)
{//将Q初始化为一个空的链队列
	Q->front=(LinkQueueNode*)malloc(sizeof(LinkQueueNode));
	if(Q->front!=NULL)
	{
		Q->rear=Q->front; //空队列
		Q->front->next=NULL;
 		return(TRUE);
	}
	else
        return(FALSE);
}

int IsEmpty(LinkQueue *Q)
{//判断队列是否为空
    if(Q->front==Q->rear)
        return(TRUE);
    else
        return(FALSE);
}

int EnterQueue(LinkQueue *Q,QueueElementType x)
{//将数据元素x插入到队列Q中
	LinkQueueNode *NewNode;
	NewNode=(LinkQueueNode*)malloc(sizeof(LinkQueueNode));
	if(NewNode!=NULL)
	{
		NewNode->data=x; //更新数据域
		NewNode->next=NULL; //更新指针域
		Q->rear->next=NewNode; //入队
		Q->rear=NewNode;//更新尾指针
		return(TRUE);
	}
	else
        return(FALSE);
}

int DeleteQueue(LinkQueue *Q)
{//将队列Q的队头元素出队，并存放到x所指的存储空间中
	int x;
	LinkQueueNode *p;
	if(Q->front==Q->rear) //判断队列是否为空
		return(FALSE);
	p=Q->front->next;
	Q->front->next=p->next; //队头元素p出队
	if(Q->rear==p)  //如果队中只有一个元素p，则p出队后成为空队
		Q->rear=Q->front;
	x=p->data;
	free(p); //释放存储空间
	return(x);
}

float Queueing(QueueElementType m,QueueElementType total)
{//银行排队问题
    LinkQueue P; //到达时间
    LinkQueue Q; //办理时间
    int R[total]; //total个窗口办理结束时间
    int i,n,x,y,min,temp,flag;
    float t=0; //总等待时间
    InitQueue(&Q);
    InitQueue(&P);
    for(i=0;i<total;i++)
    {//输入到达时间及办理业务所需时间
        scanf("%d %d",&x,&y);
        EnterQueue(&P,x);
        EnterQueue(&Q,y);
        R[i]=0;
    }
    R[0]=DeleteQueue(&P)+DeleteQueue(&Q); //初始化结束时间
    while(!IsEmpty(&P))
    {//计算总排队时间
        flag=0; //判断是否需要等待
        n=0; //最快办理窗口编号
        temp=DeleteQueue(&P); //用户到达时间
        min=R[0]; //最快办理时间
        for(i=0;i<m;i++)
            if(R[i]<min)
            {//寻找最块办理窗口
                min=R[i];
                n=i;
            }
        for(i=0;i<m;i++)
            if(R[i]<=temp)
            {//最块办理窗口是否可以办理选择窗口进行办理
                R[n]=temp+DeleteQueue(&Q);
                flag=1;
                break;
            }
        if(flag==1)
            continue; //无需等待
        else
        {//需要等待
            t+=min-temp; //总等待时间
            for(i=0;i<m;i++)
                if(R[i]==min)
                {//更新等待后窗口办理结束时间
                    R[i]+=DeleteQueue(&Q);
                    break;
                }
        }
    }
    return t;
}

int main()
{
    int m,total;
    float time;
    while(scanf("%d",&m)!=EOF)
    {// !=EOP：终端不输入时结束
        scanf("%d",&total);
        time=Queueing(m,total);
        printf("%.2f\n",time/total);
    }
    return 0;
}
