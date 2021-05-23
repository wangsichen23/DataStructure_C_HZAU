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
	QueueElementType data;     /*������*/
	struct Node *next;     /*ָ����*/
}LinkQueueNode;

typedef struct
{
	LinkQueueNode *front;
	LinkQueueNode *rear;
}LinkQueue;

/*��ʼ��������*/
int InitQueue(LinkQueue *Q)
{
	/* ��Q��ʼ��Ϊһ���յ������� */
	Q->front=(LinkQueueNode *)malloc(sizeof(LinkQueueNode));
	if(Q->front!=NULL)
	{
		Q->rear=Q->front;
		Q->front->next=NULL;
 		return(TRUE);
	}
	else return(FALSE);    /* �����*/
}

/*�ж϶����Ƿ�Ϊ��*/
int IsEmpty(LinkQueue *Q)
{
    if(Q->front==Q->rear)
        return(TRUE);
    else
        return(FALSE);
}

/*��Ӳ�����*/
int EnterQueue(LinkQueue *Q, QueueElementType x)
{
	/* ������Ԫ��x,y���뵽����Q�� */
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
	else  return(FALSE);    /* �����*/
}

/*���Ӳ�����*/
int DeleteQueue(LinkQueue *Q)
{
	/* ������Q�Ķ�ͷԪ�س��ӣ�����ŵ�x��ָ�Ĵ洢�ռ��� */
	LinkQueueNode * p;
	int x;
	if(Q->front==Q->rear)
		return(FALSE);
	p=Q->front->next;
	Q->front->next=p->next;  /* ��ͷԪ��p���� */
	if(Q->rear==p)  /* �������ֻ��һ��Ԫ��p����p���Ӻ��Ϊ�ն� */
		Q->rear=Q->front;
	x=p->data;
	free(p);   /* �ͷŴ洢�ռ� */
	return(x);
}

float Queueing(QueueElementType m, QueueElementType total)
{
    LinkQueue P;    //����ʱ��
    InitQueue(&P);
    LinkQueue Q;    //����ʱ��
    InitQueue(&Q);
    int R[total];   //����ʱ��

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
