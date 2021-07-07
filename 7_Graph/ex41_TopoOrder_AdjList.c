/*
��������ʽ��
����ĵ�һ�а���һ��������n����ʾͼ�й���n�����㡣����n������50��
�Ժ��n����ÿ����n���ÿո����������0��1�����ڵ�i�еĵ�j�����������Ϊ1�����ʾ��i��������ָ���j�����������ߣ�0��ʾû��iָ��j������ߡ���i��j��ȵ�ʱ�򣬱�֤��Ӧ������Ϊ0��
�������ʽ��
������������ͼ���л�·���������ERROR�������������š�
������������ͼ�����л�·���밴����Ŀ�����е��㷨�������ͼ�������������У�ÿ�����������һ���ո�
��ע����β������С�
���������롿
4
0 1 0 0
0 0 1 0
0 0 0 0
0 0 1 0
�����������
3 0 1 2
��˵������ע������ڽӱ�洢�ṹʱ�������������β�巨���Ա�֤��������С�������С�
*/
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
{ //�����
	int adjvex;     /*�û�ָ�򶥵��λ��*/
    struct ArcNode *nextarc;    /*ָ����һ������ָ��*/
    //OtherInfo info;       /*��û���ص���Ϣ*/
}ArcNode;

typedef struct VertexNode
{ //��ͷ���
	VertexData data; /*��������*/
	int indegree; /*���*/
    ArcNode *firstarc; /*ָ��ö����һ������ָ��*/
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
    { //��ʼ��n������Ķ����
        G->vertex[i].data=i; //��ʼ������
        G->vertex[i].firstarc=(ArcNode*)malloc(sizeof(ArcNode));
    }
    for(i=0;i<G->vexnum;i++)
    {
        p=G->vertex[i].firstarc;
        for(j=0;j<G->vexnum;j++)
        { //���뻡���
            scanf("%d",&k);
            if(k)
            { //���������0���򽫽�����
                p->adjvex=G->vertex[j].data;
                p->nextarc=(ArcNode*)malloc(sizeof(ArcNode));
                p=p->nextarc;
            }
        }
        p->adjvex=2046;
    }
}

void FindID(AdjList G, int indegree[MAX_VERTEX_NUM])
{ //����������
    int i;
    ArcNode *p;
    for(i=0;i<G.vexnum;i++) //��ʼ��
        indegree[i]=0;
    for(i=0;i<G.vexnum;i++)
    {
        p=G.vertex[i].firstarc;
        while(p->adjvex!=2046)
        { //���ڽӵ�
            indegree[p->adjvex]++;
            p=p->nextarc;
        }
    }
}

void TopoSort_AdjList(AdjList G)
{ //�����ڽӱ����������
    SeqStack S;
    int indegree[MAX_VERTEX_NUM];
    int i,j,count=0;
    ArcNode *p;
    FindID(G, indegree); //����������
    InitStack(&S); //��ʼ������ջ
    for(i=0;i<G.vexnum;i++)
        if(indegree[i]==0)
            Push(&S,i); //���Ϊ0�Ķ�����ջ
    while(!StackEmpty(&S)) //ջ���գ� δ����
    {
        Pop(&S, &i); //��ջһ��
        printf("%d ",i); //���
        count++; //����������
        p=G.vertex[i].firstarc;
        while(p->adjvex!=2046) // vi�����ڽӵ�ȼ�1
        {
            j=p->adjvex; // p�������
            indegree[j]--; //��ȼ�1
            if(!indegree[j])
                Push(&S, j); //���Ϊ0����ջ
            p=p->nextarc; //��һ��
        }
    }
    if(count<G.vexnum)
        printf("ERROR"); //������ͼ���л�·
}

int main()
{
    AdjList G;
    CreateDG(&G);
    TopoSort_AdjList(G);
    return 0;
}
