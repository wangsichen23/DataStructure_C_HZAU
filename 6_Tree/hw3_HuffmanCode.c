#include <stdio.h>
//#include <stdlib.h>
#include <string.h>

#define N 100
#define M 2*N-1

typedef char *HuffmanCode[N+1];

typedef struct
{
	int weight; /* 用来存放各个结点的权值*/
	int parent;
	int lchild;
	int rchild; /*指向双亲、孩子结点的指针*/
}HTNode, HuffmanTree[M+1];   /*动态分配数组，存储哈夫曼树*/

void select(HuffmanTree ht,int n,int *s1,int *s2)
{
    int i,flag1=0,flag2=0;
    int min=65536;
    for(i=1;i<=n;i++)
    {
        if(ht[i].weight<min && ht[i].parent==0)
        {
            min=ht[i].weight;
            flag1=i;
        }
    }
    min=65536;
    for(i=1;i<=n;i++)
    {
        if(ht[i].weight<min && ht[i].parent==0 && i!=flag1)
        {
            min=ht[i].weight;
            flag2=i;
        }
    }
    *s1=flag1;
    *s2=flag2;
}

void CrtHuffmanTree(HuffmanTree ht,int w[ ],int n) //构造哈夫曼树ht[M+1]， n个叶子， w[ ]存放n个权值
{
    int i,m,s1,s2;
    for(i=1;i<=n;i++)
    {
        ht[i].weight=w[i];
        ht[i].parent=0;
        ht[i].lchild=0;
        ht[i].rchild=0;
    }
    m=2*n-1; //m个树结点
    for(i=n+1;i<=m;i++)
    {
        ht[i].weight=0;
        ht[i].parent=0;
        ht[i].lchild=0;
        ht[i].rchild=0;
    }
    for(i=n+1;i<=m;i++) //n+1非叶， 构建关系
    {
        select(ht,i-1,&s1,&s2); //1~i-1中选择两个结点， 权重最小且无父节点
        ht[i].weight=ht[s1].weight+ht[s2].weight;
        ht[i].lchild=s1;
        ht[i].rchild=s2; //置i的孩子节点
        ht[s1].parent=i;
        ht[s2].parent=i; //置s1,s2的双亲节点
    }
}

void CrtHuffmanCode(HuffmanTree ht, HuffmanCode hc, int n)
{
	char *cd;
	int i,c,p,start;
	cd=(char*)malloc(n*sizeof(char));  /*分配求当前编码的工作空间*/
	cd[n-1]='\0';   /*从右向左逐位存放编码，首先存放编码结束符*/
	for(i=1;i<=n;i++)  /*求n个叶子结点对应的哈夫曼编码*/
	{
		start=n-1;    /*初始化编码起始指针*/
		c=i;
		p=ht[i].parent;
		while(p!=0) //从底层叶子上推到根
        {
            --start;
            if(ht[p].lchild==c)
                cd[start]='0'; //标号c是左孩子
            else
                cd[start]='1';
            c=p;
            p=ht[p].parent; // 向上找
        }
        hc[i]=(char *)malloc((n-start)*sizeof(char));  /*为第i个编码分配空间*/
        strcpy(hc[i],&cd[start]);
	}
	//free(cd);
	for(i=1;i<=n;i++)
		printf("%s\n",hc[i]);
}

int main()
{
    int i,n;
    int w[100];
    HuffmanCode hc;
    HuffmanTree ht;

    scanf("%d",&n);
    for(i=1;i<=n;i++)
        scanf("%d",&w[i]);

    CrtHuffmanTree(ht,w,n);
    CrtHuffmanCode(ht,hc,n);

    return 0;
}
