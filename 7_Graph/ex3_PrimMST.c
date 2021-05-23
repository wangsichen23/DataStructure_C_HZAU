#include <stdio.h>

#define MAX_VERTEX_NUM 50 //顶点个数
#define INFINITY 32768 //表示极大值∞

typedef struct
{ //定义图
    int vexs[MAX_VERTEX_NUM]; //顶点表
    int AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //二维数组存储邻接矩阵
    int vexnum,arcnum; //顶点数与边数
}Graph;

typedef struct
{ //定义最小生成树的边
    int begin,end; //边顶点序号
    int cost; //边上的权值
}TreeEdge;

void CreateUDN(Graph *G)
{ //创建无向网
    int i,j;
    int a,b,c;
    scanf("%d %d",&(G->vexnum),&(G->arcnum)); //输入定点数与边数
    for(i=0;i<G->vexnum;i++)
        for(j=0;j<G->vexnum;j++)
            G->AdjMatrix[i][j]=INFINITY; //初始化邻接矩阵
    for(i=0;i<G->arcnum;i++)
    { //输入邻接矩阵
        scanf("%d %d %d",&a,&b,&c);
        G->AdjMatrix[a-1][b-1]=c; //上三角矩阵
        G->AdjMatrix[b-1][a-1]=c; //下三角矩阵
    }
}

void PrimMST(Graph G)
{ //Prim算法
    int i,j,k,sum=0,n=G.vexnum,minCost=0;
    int lowerCost[MAX_VERTEX_NUM],closeVertex[MAX_VERTEX_NUM];
    TreeEdge close[MAX_VERTEX_NUM]; //最小生成树
    for(i=0;i<n;i++)
    { //初始化
        lowerCost[i]=G.AdjMatrix[0][i]; //V-U集合中各顶点与U集合中各顶点距离
        closeVertex[i]=0; //每条边在U集合中对应的顶点
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
        /*保存最小权值边的顶点及权值*/
        lowerCost[k]=0;
        close[i-1].begin=closeVertex[k];
        close[i-1].end=k;
        close[i-1].cost=minCost;
        sum+=minCost;
        for(j=1;j<n;j++)
            if(G.AdjMatrix[k][j]<lowerCost[j])
            { //修改其它顶点边的权值以及最小生成树顶点序号
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
