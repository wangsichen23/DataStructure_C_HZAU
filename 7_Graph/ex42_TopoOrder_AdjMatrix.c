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
{
    int data;//无权图用1/0表示是否相邻，对带权图为权值类型
    //OtherInfo info; //这里写扩展信息
}ArcNode;

typedef struct
{
    VertexData vertex[MAX_VERTEX_NUM];//定义顶点向量
    ArcNode arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//定义邻接矩阵
    int vexnum,arcnum;//定义顶点数和边数
    GraphKind kind;
}AdjMatrix;

void CreateDG(AdjMatrix *G)
{ //创建有向图
    int i,j;
    scanf("%d",&G->vexnum);//输入无向图的顶点数
    for(i=0;i<G->vexnum;i++)
        for(j=0;j<G->vexnum;j++)
            scanf("%d",&G->arcs[i][j].data);
}

void FindID(AdjMatrix G, int indegree[MAX_VERTEX_NUM])
{ //求各顶点入度
    int i,j;
    for(i=0;i<G.vexnum;i++) //初始化
        indegree[i]=0;
    for(i=0;i<G.vexnum;i++)
        for(j=0;j<G.vexnum;j++)
            if(G.arcs[i][j].data)
                indegree[j]++;
}

void TopoSort_AdjMatrix(AdjMatrix G)
{ //基于邻接矩阵的拓扑排序
    int i,j,count=0;
    int indegree[MAX_VERTEX_NUM];
    SeqStack S;
    FindID(G, indegree); //求各顶点入度
    InitStack(&S); //初始化辅助栈
    for(i=0;i<G.vexnum;i++)
        if(!indegree[i])
            Push(&S,i); //入度为0的顶点入栈
    while(!StackEmpty(&S)) //栈不空，未结束
    {
        Pop(&S, &i); //出栈一个
        printf("%d ",i); //输出
        count++; //输出顶点计数
        for(j=0;j<G.vexnum;j++)
            if(G.arcs[i][j].data)
            { //出栈结点对应的结点入度减1
                indegree[j]--;
                if(!indegree[j])
                    Push(&S,j);//若入度减为0，则入栈
            }
    }
    if(count<G.vexnum)
        printf("ERROR"); //该有向图含有回路
}

int main()
{
    AdjMatrix G;
    CreateDG(&G);
    TopoSort_AdjMatrix(G);
    return 0;
}
