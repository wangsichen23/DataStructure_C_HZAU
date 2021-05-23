#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX_VERTEX_NUM 50 //顶点个数
#define INFINITY 32768 //表示极大值∞

#define OK   1
#define ERROR  -1
#define TRUE 1
#define FALSE 0

#define ElemType int
#define MAXSIZE 50

/*定义队列*/
typedef struct Node
{ //队列的结点形式
    ElemType data;
    struct Node *next;
}LinkQueueNode;

typedef struct
{ //队列的前后指针
    LinkQueueNode *prior;
    LinkQueueNode *rear;
}LinkQueue;

int InitQueue(LinkQueue *Q)
{ //将Q初始化为一个空的队列
    Q->prior=(LinkQueueNode *)malloc(sizeof(LinkQueueNode));
    if(Q->prior!=NULL)
    {
        Q->rear=Q->prior;
        Q->prior->next=NULL;
        return(TRUE);
    }
    else return (FALSE);    //表示溢出
}

int EnterQueue(LinkQueue *Q,ElemType x)
{ //将元素x入队
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
        return(FALSE); //溢出警告
}

int DeleteQueue(LinkQueue *Q,ElemType *x)
{ //将元素x出队
    LinkQueueNode *p;
    if(Q->prior==Q->rear)
        return(FALSE);
    p=Q->prior->next;
    Q->prior->next=p->next;
    if(Q->rear==p) //队中只有一个元素p，则p出队后成为空队
        Q->rear=Q->prior;
    *x=p->data;
    free(p);
    return(TRUE);
}

int Empty(LinkQueue Q)
{ //判断队列是否为空
    if(Q.prior==Q.rear)
        return(TRUE);
    else
        return(FALSE);
}

/*定义无向图*/
typedef enum{DG,DN,UDG,UDN} GraphKind; //图的种类：DG表示有向图，DN表示有向网，UDG表示无向图，UDN表示无向网

typedef char VertexData; //假设顶点数据为字符型

typedef struct ArcNode
{ //弧结点
	int adjvex;     /*该弧指向顶点的位置*/
    struct ArcNode *nextarc;    /*指向下一条弧的指针*/
    //OtherInfo info;       /*与该弧相关的信息*/
}ArcNode;

typedef struct VertexNode
{ //表头结点
	VertexData data;        /*顶点数据*/
    ArcNode *firstarc;    /*指向该顶点第一条弧的指针*/
}VertexNode;

typedef struct
{ //邻接表
    VertexNode vertex[MAX_VERTEX_NUM]; /*表头结点*/
    int vexnum,arcnum;               /*图的顶点数和弧数*/
    GraphKind kind;                        /*图的种类标志*/
}AdjList;           /*基于邻接表的图(Adjacency List Graph)*/

void CreateDG(AdjList *G)
{ //创建有向图
    int i,j,k;
    ArcNode *p;
    scanf("%d",&G->vexnum);//输入有向图的顶点数
    for (i=0;i<G->vexnum;i++)
    { //输入表头结点
        scanf("%d",&G->vertex[i].data);
        G->vertex[i].firstarc=(ArcNode*)malloc(sizeof(ArcNode));
    }
    for(i=0;i<G->vexnum;i++)
    { //输入弧结点
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
{ //找顶点位置
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
{ //求x的第一个邻接点
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
{ //求v相对于w的下一个邻接点
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
{ //广度优先搜索图g中v0所在的连通子图
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
        w=FirstAdjVertex(G,v);   //求v的第一个邻接点
        while(w!=ERROR)
        {
            if(!visited[w])
            {
                printf("%d ",G.vertex[w].data);
                visited[w]=TRUE;
                EnterQueue(&Q,w);
            }
            w=NextAdjVertex(G,v,w);   //求v相对于w的下一个邻接点
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
