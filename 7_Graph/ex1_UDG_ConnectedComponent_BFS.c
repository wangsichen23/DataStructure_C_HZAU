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
typedef enum{DG,DN,UDG,UDN} Graphkind; //图的种类：DG表示有向图，DN表示有向网，UDG表示无向图，UDN表示无向网

typedef char VertexData; //假设顶点数据为字符型

typedef struct ArcNode
{
    int adj;//无权图用1/0表示是否相邻，对带权图为权值类型
    //OtherInfo info; //这里写扩展信息
}ArcNode;

typedef struct
{
    VertexData vertex[MAX_VERTEX_NUM];//定义顶点向量
    ArcNode arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//定义邻接矩阵
    int vexnum,arcnum;//定义顶点数和边数
    Graphkind kind;
}AdjMatrix;

void CreateUDG(AdjMatrix *G)
{ //创建无向图
    int i,j;
    scanf("%d",&G->vexnum);//输入无向图的顶点数
    for(i=0;i<G->vexnum;i++)
        for(j=0;j<G->vexnum;j++)
            scanf("%d",&G->arcs[i][j].adj);
}

int LocateVertex(AdjMatrix *G,VertexData v)
{ //确定顶点v在图G中的位置
    int k,j=ERROR;
    for(k=0;k<G->vexnum;k++)
        if(G->vertex[k]==v)
        {
            j=k;
            break;
        }
    return(j);
}

int FirstAdjVertex(AdjMatrix g,int x)
{ //求x的第一个邻接点
    int i;
    for(i=0;i<g.vexnum;i++)
    {
        if(g.arcs[x][i].adj!=0)
            return(i);
    }
    return(ERROR);
}

int NextAdjVertex(AdjMatrix g,int v,int w,int visited[])
{ //求v相对于w的下一个邻接点
    int i;
    for(i=w;i<g.vexnum;i++)
    {
        if(g.arcs[v][i].adj!=0 && visited[i]!=1)
            return(i);
    }
    return(ERROR);
}

void BFSConnectedComponentCounter(AdjMatrix g)
{//广度优先搜索无向图g的联通分量个数
    LinkQueue Q;
    int i,v,w,v0=0,n=0;
    int visited[MAX_VERTEX_NUM];
    for(i=0;i<g.vexnum;i++)
        visited[i]=FALSE;
    for(i=0;i<g.vexnum;i++)
        if(g.arcs[i][0].adj==0)
        { //寻找初始结点
            v0=i;
            break;
        }
    while(visited[v0]!=TRUE)
    {
        visited[v0]=TRUE;
        InitQueue(&Q);
        EnterQueue(&Q,v0);
        while(!Empty(Q))
        {
            DeleteQueue(&Q,&v); //出队
            w=FirstAdjVertex(g,v);   //求v的第一个邻接点
            while(w!=-1) //v0的邻接点w存在， 依次访问邻接点
            {
                if(!visited[w]) //且未被访问
                {
                    visited[w]=TRUE; //访问
                    EnterQueue(&Q,w); //入队
                }
                w=NextAdjVertex(g,v,w,visited); //求v相对于w的下一个邻接点
            }
        }
        n++;
        for(i=0;i<g.vexnum;i++)
            if(visited[i]==0)
            { //寻找初始结点
                v0=i;
                break;
            }
    }
    printf("%d",n);
}

int main()
{
    AdjMatrix UDG;
    CreateUDG(&UDG);
    BFSConnectedComponentCounter(UDG);
    return 0;
}
