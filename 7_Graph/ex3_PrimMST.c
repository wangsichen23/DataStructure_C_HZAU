#include <stdio.h>

#define MAX_VERTEX_NUM 50 //�������
#define INFINITY 32768 //��ʾ����ֵ��

typedef struct
{ //����ͼ
    int vexs[MAX_VERTEX_NUM]; //�����
    int AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //��ά����洢�ڽӾ���
    int vexnum,arcnum; //�����������
}Graph;

typedef struct
{ //������С�������ı�
    int begin,end; //�߶������
    int cost; //���ϵ�Ȩֵ
}TreeEdge;

void CreateUDN(Graph *G)
{ //����������
    int i,j;
    int a,b,c;
    scanf("%d %d",&(G->vexnum),&(G->arcnum)); //���붨���������
    for(i=0;i<G->vexnum;i++)
        for(j=0;j<G->vexnum;j++)
            G->AdjMatrix[i][j]=INFINITY; //��ʼ���ڽӾ���
    for(i=0;i<G->arcnum;i++)
    { //�����ڽӾ���
        scanf("%d %d %d",&a,&b,&c);
        G->AdjMatrix[a-1][b-1]=c; //�����Ǿ���
        G->AdjMatrix[b-1][a-1]=c; //�����Ǿ���
    }
}

void PrimMST(Graph G)
{ //Prim�㷨
    int i,j,k,sum=0,n=G.vexnum,minCost=0;
    int lowerCost[MAX_VERTEX_NUM],closeVertex[MAX_VERTEX_NUM];
    TreeEdge close[MAX_VERTEX_NUM]; //��С������
    for(i=0;i<n;i++)
    { //��ʼ��
        lowerCost[i]=G.AdjMatrix[0][i]; //V-U�����и�������U�����и��������
        closeVertex[i]=0; //ÿ������U�����ж�Ӧ�Ķ���
    }
    for(i=1;i<n;i++)
    {
        minCost=INFINITY;
        k=1;
        for(j=1;j<n;j++)
            if(lowerCost[j]!=0 && lowerCost[j]<minCost)
            {
                minCost=lowerCost[j];
                k=j;
            }
        /*������СȨֵ�ߵĶ��㼰Ȩֵ*/
        lowerCost[k]=0;
        close[i-1].begin=closeVertex[k];
        close[i-1].end=k;
        close[i-1].cost=minCost;
        sum+=minCost;
        for(j=1;j<n;j++)
            if(G.AdjMatrix[k][j]<lowerCost[j])
            { //�޸���������ߵ�Ȩֵ�Լ���С�������������
                lowerCost[j]=G.AdjMatrix[k][j];
                closeVertex[j]=k;
            }
    }
    for(i=0;i<n-1;i++)
        printf("%d-%d:%d\n",close[i].begin+1,close[i].end+1,close[i].cost);
    printf("%d",sum);
}

int main()
{
    Graph G;
    CreateUDN(&G);
    PrimMST(G);
    return 0;
}
