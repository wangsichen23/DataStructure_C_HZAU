/*
【输入形式】
输入的第一行包含一个正整数n，表示图中共有n个顶点。其中n不超过50。
以后的n行中每行有n个用空格隔开的整数0或1，对于第i行的第j个整数，如果为1，则表示第i个顶点有指向第j个顶点的有向边，0表示没有i指向j的有向边。当i和j相等的时候，保证对应的整数为0。
【输出形式】
如果读入的有向图含有回路，请输出“ERROR”，不包括引号。
如果读入的有向图不含有回路，请按照题目描述中的算法依次输出图的拓扑有序序列，每个整数后输出一个空格。
请注意行尾输出换行。
【样例输入】
4
0 1 0 0
0 0 1 0
0 0 0 0
0 0 1 0
【样例输出】
3 0 1 2
【说明】请注意采用邻接表存储结构时，链表创建需采用尾插法，以保证后续结点从小到大排列。
*/
#include <stdio.h>
#include <malloc.h>
#include <math.h>

#define OK  1
#define ERROR  0
#define TRUE 1
#define FALSE 0

#define Stack_Size 100 //栈长
#define MAX_VERTEX_NUM 100 //顶点个数

typedef struct
{
    char elem[Stack_Size];
    int top;
}SeqStack;

void InitStack(SeqStack *S)
{
    S->top=-1;
}

int Push(SeqStack *S,int x)
{
    if(S->top==Stack_Size-1)
        return(FALSE);
    S->top++;
    S->elem[S->top]=x;
    return(TRUE);
}

int Pop(SeqStack *S,int *x)
{
    if(S->top==-1)
        return(FALSE);
    else
    {
        *x=S->elem[S->top];
        S->top--;
        return(TRUE);
    }
}

int StackEmpty(SeqStack *S)
{
    if(S->top==-1)
        return(TRUE);
    else
        return(FALSE);
}

typedef enum{DG,DN,UDG,UDN} GraphKind; //图的种类：DG表示有向图，DN表示有向网，UDG表示无向图，UDN表

typedef int VertexData; //假设顶点数据为字符型

typedef struct ArcNode
{ //弧结点
	int adjvex;     /*该弧指向顶点的位置*/
    struct ArcNode *nextarc;    /*指向下一条弧的指针*/
    //OtherInfo info;       /*与该弧相关的信息*/
}ArcNode;

typedef struct VertexNode
{ //表头结点
	VertexData data; /*顶点数据*/
	int indegree; /*入度*/
    ArcNode *firstarc; /*指向该顶点第一条弧的指针*/
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
    scanf("%d",&G->vexnum);//输入无向图的顶点数
    for (i=0;i<G->vexnum;i++)
    { //初始化n个顶点的顶点表
        G->vertex[i].data=i; //初始化顶点
        G->vertex[i].firstarc=(ArcNode*)malloc(sizeof(ArcNode));
    }
    for(i=0;i<G->vexnum;i++)
    {
        p=G->vertex[i].firstarc;
        for(j=0;j<G->vexnum;j++)
        { //输入弧结点
            scanf("%d",&k);
            if(k)
            { //若输入结点非0，则将结点加入
                p->adjvex=G->vertex[j].data;
                p->nextarc=(ArcNode*)malloc(sizeof(ArcNode));
                p=p->nextarc;
            }
        }
        p->adjvex=2046;
    }
}

void FindID(AdjList G, int indegree[MAX_VERTEX_NUM])
{ //求各顶点入度
    int i;
    ArcNode *p;
    for(i=0;i<G.vexnum;i++) //初始化
        indegree[i]=0;
    for(i=0;i<G.vexnum;i++)
    {
        p=G.vertex[i].firstarc;
        while(p->adjvex!=2046)
        { //有邻接点
            indegree[p->adjvex]++;
            p=p->nextarc;
        }
    }
}

void TopoSort_AdjList(AdjList G)
{ //基于邻接表的拓扑排序
    SeqStack S;
    int indegree[MAX_VERTEX_NUM];
    int i,j,count=0;
    ArcNode *p;
    FindID(G, indegree); //求各顶点入度
    InitStack(&S); //初始化辅助栈
    for(i=0;i<G.vexnum;i++)
        if(indegree[i]==0)
            Push(&S,i); //入度为0的顶点入栈
    while(!StackEmpty(&S)) //栈不空， 未结束
    {
        Pop(&S, &i); //出栈一个
        printf("%d ",i); //输出
        count++; //输出顶点计数
        p=G.vertex[i].firstarc;
        while(p->adjvex!=2046) // vi所有邻接点度减1
        {
            j=p->adjvex; // p结点的序号
            indegree[j]--; //入度减1
            if(!indegree[j])
                Push(&S, j); //入度为0，入栈
            p=p->nextarc; //下一个
        }
    }
    if(count<G.vexnum)
        printf("ERROR"); //该有向图含有回路
}

int main()
{
    AdjList G;
    CreateDG(&G);
    TopoSort_AdjList(G);
    return 0;
}
