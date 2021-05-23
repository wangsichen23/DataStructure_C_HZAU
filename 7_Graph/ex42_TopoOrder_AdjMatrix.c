#include <stdio.h>
#include <malloc.h>
#include <math.h>

#define OK  1
#define ERROR  0
#define TRUE 1
#define FALSE 0

#define Stack_Size 100 //ջ��
#define MAX_VERTEX_NUM 100 //�������

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

typedef enum{DG,DN,UDG,UDN} GraphKind; //ͼ�����ࣺDG��ʾ����ͼ��DN��ʾ��������UDG��ʾ����ͼ��UDN��

typedef int VertexData; //���趥������Ϊ�ַ���

typedef struct ArcNode
{
    int data;//��Ȩͼ��1/0��ʾ�Ƿ����ڣ��Դ�ȨͼΪȨֵ����
    //OtherInfo info; //����д��չ��Ϣ
}ArcNode;

typedef struct
{
    VertexData vertex[MAX_VERTEX_NUM];//���嶥������
    ArcNode arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];//�����ڽӾ���
    int vexnum,arcnum;//���嶥�����ͱ���
    GraphKind kind;
}AdjMatrix;

void CreateDG(AdjMatrix *G)
{ //��������ͼ
    int i,j;
    scanf("%d",&G->vexnum);//��������ͼ�Ķ�����
    for(i=0;i<G->vexnum;i++)
        for(j=0;j<G->vexnum;j++)
            scanf("%d",&G->arcs[i][j].data);
}

void FindID(AdjMatrix G, int indegree[MAX_VERTEX_NUM])
{ //����������
    int i,j;
    for(i=0;i<G.vexnum;i++) //��ʼ��
        indegree[i]=0;
    for(i=0;i<G.vexnum;i++)
        for(j=0;j<G.vexnum;j++)
            if(G.arcs[i][j].data)
                indegree[j]++;
}

void TopoSort_AdjMatrix(AdjMatrix G)
{ //�����ڽӾ������������
    int i,j,count=0;
    int indegree[MAX_VERTEX_NUM];
    SeqStack S;
    FindID(G, indegree); //����������
    InitStack(&S); //��ʼ������ջ
    for(i=0;i<G.vexnum;i++)
        if(!indegree[i])
            Push(&S,i); //���Ϊ0�Ķ�����ջ
    while(!StackEmpty(&S)) //ջ���գ�δ����
    {
        Pop(&S, &i); //��ջһ��
        printf("%d ",i); //���
        count++; //����������
        for(j=0;j<G.vexnum;j++)
            if(G.arcs[i][j].data)
            { //��ջ����Ӧ�Ľ����ȼ�1
                indegree[j]--;
                if(!indegree[j])
                    Push(&S,j);//����ȼ�Ϊ0������ջ
            }
    }
    if(count<G.vexnum)
        printf("ERROR"); //������ͼ���л�·
}

int main()
{
    AdjMatrix G;
    CreateDG(&G);
    TopoSort_AdjMatrix(G);
    return 0;
}
