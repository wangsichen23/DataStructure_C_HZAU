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
typedef enum{DG,DN,UDG,UDN} Graphkind; //ͼ�����ࣺDG��ʾ����ͼ��DN��ʾ��������UDG��ʾ����ͼ��UDN��ʾ������

typedef char VertexData; //���趥������Ϊ�ַ���

typedef struct ArcNode
{
    int adj;//��Ȩͼ��1/0��ʾ�Ƿ����ڣ��Դ�ȨͼΪȨֵ����
    //OtherInfo info; //����д��չ��Ϣ
}ArcNode;

typedef struct
{
    VertexData vertex[MAX_VERTEX_NUM];//���嶥������
    ArcNode arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//�����ڽӾ���
    int vexnum,arcnum;//���嶥�����ͱ���
    Graphkind kind;
}AdjMatrix;

void CreateUDG(AdjMatrix *G)
{ //��������ͼ
    int i,j;
    scanf("%d",&G->vexnum);//��������ͼ�Ķ�����
    for(i=0;i<G->vexnum;i++)
        for(j=0;j<G->vexnum;j++)
            scanf("%d",&G->arcs[i][j].adj);
}

int LocateVertex(AdjMatrix *G,VertexData v)
{ //ȷ������v��ͼG�е�λ��
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
{ //��x�ĵ�һ���ڽӵ�
    int i;
    for(i=0;i<g.vexnum;i++)
    {
        if(g.arcs[x][i].adj!=0)
            return(i);
    }
    return(ERROR);
}

int NextAdjVertex(AdjMatrix g,int v,int w,int visited[])
{ //��v�����w����һ���ڽӵ�
    int i;
    for(i=w;i<g.vexnum;i++)
    {
        if(g.arcs[v][i].adj!=0 && visited[i]!=1)
            return(i);
    }
    return(ERROR);
}

void BFSConnectedComponentCounter(AdjMatrix g)
{//���������������ͼg����ͨ��������
    LinkQueue Q;
    int i,v,w,v0=0,n=0;
    int visited[MAX_VERTEX_NUM];
    for(i=0;i<g.vexnum;i++)
        visited[i]=FALSE;
    for(i=0;i<g.vexnum;i++)
        if(g.arcs[i][0].adj==0)
        { //Ѱ�ҳ�ʼ���
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
            DeleteQueue(&Q,&v); //����
            w=FirstAdjVertex(g,v);   //��v�ĵ�һ���ڽӵ�
            while(w!=-1) //v0���ڽӵ�w���ڣ� ���η����ڽӵ�
            {
                if(!visited[w]) //��δ������
                {
                    visited[w]=TRUE; //����
                    EnterQueue(&Q,w); //���
                }
                w=NextAdjVertex(g,v,w,visited); //��v�����w����һ���ڽӵ�
            }
        }
        n++;
        for(i=0;i<g.vexnum;i++)
            if(visited[i]==0)
            { //Ѱ�ҳ�ʼ���
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
