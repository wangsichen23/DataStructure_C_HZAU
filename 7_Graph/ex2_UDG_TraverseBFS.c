#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX_VERTEX_NUM 50 //�������
#define INFINITY 32768 //��ʾ����ֵ��

#define OK   1
#define ERROR  -1
#define TRUE 1
#define FALSE 0

#define ElemType int
#define MAXSIZE 50

/*�������*/
typedef struct Node
{ //���еĽ����ʽ
    ElemType data;
    struct Node *next;
}LinkQueueNode;

typedef struct
{ //���е�ǰ��ָ��
    LinkQueueNode *prior;
    LinkQueueNode *rear;
}LinkQueue;

int InitQueue(LinkQueue *Q)
{ //��Q��ʼ��Ϊһ���յĶ���
    Q->prior=(LinkQueueNode *)malloc(sizeof(LinkQueueNode));
    if(Q->prior!=NULL)
    {
        Q->rear=Q->prior;
        Q->prior->next=NULL;
        return(TRUE);
    }
    else return (FALSE);    //��ʾ���
}

int EnterQueue(LinkQueue *Q,ElemType x)
{ //��Ԫ��x���
    LinkQueueNode *NewNode;
    NewNode=(LinkQueueNode *)malloc(sizeof(LinkQueueNode));
    if(NewNode!=NULL)
    {
        NewNode->data=x;
        NewNode->next=NULL;
        Q->rear->next=NewNode;
        Q->rear=NewNode;
        return(TRUE);
    }
    else
        return(FALSE); //�������
}

int DeleteQueue(LinkQueue *Q,ElemType *x)
{ //��Ԫ��x����
    LinkQueueNode *p;
    if(Q->prior==Q->rear)
        return(FALSE);
    p=Q->prior->next;
    Q->prior->next=p->next;
    if(Q->rear==p) //����ֻ��һ��Ԫ��p����p���Ӻ��Ϊ�ն�
        Q->rear=Q->prior;
    *x=p->data;
    free(p);
    return(TRUE);
}

int Empty(LinkQueue Q)
{ //�ж϶����Ƿ�Ϊ��
    if(Q.prior==Q.rear)
        return(TRUE);
    else
        return(FALSE);
}

/*��������ͼ*/
typedef enum{DG,DN,UDG,UDN} GraphKind; //ͼ�����ࣺDG��ʾ����ͼ��DN��ʾ��������UDG��ʾ����ͼ��UDN��ʾ������

typedef char VertexData; //���趥������Ϊ�ַ���

typedef struct ArcNode
{ //�����
	int adjvex;     /*�û�ָ�򶥵��λ��*/
    struct ArcNode *nextarc;    /*ָ����һ������ָ��*/
    //OtherInfo info;       /*��û���ص���Ϣ*/
}ArcNode;

typedef struct VertexNode
{ //��ͷ���
	VertexData data;        /*��������*/
    ArcNode *firstarc;    /*ָ��ö����һ������ָ��*/
}VertexNode;

typedef struct
{ //�ڽӱ�
    VertexNode vertex[MAX_VERTEX_NUM]; /*��ͷ���*/
    int vexnum,arcnum;               /*ͼ�Ķ������ͻ���*/
    GraphKind kind;                        /*ͼ�������־*/
}AdjList;           /*�����ڽӱ��ͼ(Adjacency List Graph)*/

void CreateDG(AdjList *G)
{ //��������ͼ
    int i,j,k;
    ArcNode *p;
    scanf("%d",&G->vexnum);//��������ͼ�Ķ�����
    for (i=0;i<G->vexnum;i++)
    { //�����ͷ���
        scanf("%d",&G->vertex[i].data);
        G->vertex[i].firstarc=(ArcNode*)malloc(sizeof(ArcNode));
    }
    for(i=0;i<G->vexnum;i++)
    { //���뻡���
        p=G->vertex[i].firstarc;
        for(j=0;j<G->vexnum;j++)
        {
            scanf("%d",&k);
            if(k)
            {
                p->adjvex=G->vertex[j].data;
                p->nextarc=(ArcNode*)malloc(sizeof(ArcNode));
                p=p->nextarc;
            }
        }
        p=NULL;
    }
}

int LocateVertex(AdjList *G,VertexData v)
{ //�Ҷ���λ��
    int k,j=ERROR;
    for(k=0;k<G->vexnum;k++)
        if(G->vertex[k].data==v)
        {
            j=k;
            break;
        }
    return(j);
}

int FirstAdjVertex(AdjList G,int x)
{ //��x�ĵ�һ���ڽӵ�
    int i;
    if(G.vertex[x].firstarc!=NULL)
    {
        i=G.vertex[x].firstarc->adjvex;
        i=LocateVertex(&G,i);
        return(i);
    }
    return(ERROR);
}

int NextAdjVertex(AdjList G,int v,int w)
{ //��v�����w����һ���ڽӵ�
    int i;
    ArcNode *p;
    p=G.vertex[v].firstarc;
    while(p->nextarc!=NULL&&LocateVertex(&G,p->adjvex)!=w)
        p=p->nextarc;
    if(p->nextarc==NULL)
        return(ERROR);
    else
    {
        i=LocateVertex(&G,p->nextarc->adjvex);
        return(i);
    }
}

void BreadthFirstSearch(AdjList G, int v0)
{ //�����������ͼg��v0���ڵ���ͨ��ͼ
    LinkQueue Q;
    int i,v,w=0;
    int visited[MAX_VERTEX_NUM];
    for(i=0;i<G.vexnum;i++)
        visited[i]=FALSE;
    printf("%d ",G.vertex[w].data);
    visited[v0]=TRUE;
    InitQueue(&Q);
    EnterQueue(&Q,v0);
    while(!Empty(Q))
    {
        DeleteQueue(&Q,&v);
        w=FirstAdjVertex(G,v);   //��v�ĵ�һ���ڽӵ�
        while(w!=ERROR)
        {
            if(!visited[w])
            {
                printf("%d ",G.vertex[w].data);
                visited[w]=TRUE;
                EnterQueue(&Q,w);
            }
            w=NextAdjVertex(G,v,w);   //��v�����w����һ���ڽӵ�
        }
    }
}

int main()
{
    AdjList DG;
    CreateDG(&DG);
    BreadthFirstSearch(DG,0);
    return 0;
}
