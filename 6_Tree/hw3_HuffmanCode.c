/*
������������
����n���ַ�����Ӧ��Ȩֵ������һ�ù���������
�Ե���������ÿһ���ַ���Ӧ�Ĺ��������룬�����������

��������ʽ��
����ĵ�һ�а���һ��������n����ʾ����n���ַ���Ҫ���롣����n������100��
�ڶ�������n���ÿո���������������ֱ��ʾn���ַ���Ȩֵ��

�������ʽ��
��n�У�ÿ��һ���ַ�������ʾ��Ӧ�ַ��Ĺ��������롣

��ע�⡿
��֤ÿ������������������ȨֵС���������ͬȨֵ�ģ����ȳ��ֵ�����������

���������롿
8
5 29 7 8 14 23 3 11

�����������
0001
10
1110
1111
110
01
0000
001
*/
#include <stdio.h>
#include <string.h>

#define N 100
#define M 2*N-1

typedef char *HuffmanCode[N+1];

typedef struct
{
	int weight; /* ������Ÿ�������Ȩֵ*/
	int parent;
	int lchild;
	int rchild; /*ָ��˫�ס����ӽ���ָ��*/
}HTNode, HuffmanTree[M+1];   /*��̬�������飬�洢��������*/

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

void CrtHuffmanTree(HuffmanTree ht,int w[ ],int n) //�����������ht[M+1]�� n��Ҷ�ӣ� w[ ]���n��Ȩֵ
{
    int i,m,s1,s2;
    for(i=1;i<=n;i++)
    {
        ht[i].weight=w[i];
        ht[i].parent=0;
        ht[i].lchild=0;
        ht[i].rchild=0;
    }
    m=2*n-1; //m�������
    for(i=n+1;i<=m;i++)
    {
        ht[i].weight=0;
        ht[i].parent=0;
        ht[i].lchild=0;
        ht[i].rchild=0;
    }
    for(i=n+1;i<=m;i++) //n+1��Ҷ�� ������ϵ
    {
        select(ht,i-1,&s1,&s2); //1~i-1��ѡ��������㣬 Ȩ����С���޸��ڵ�
        ht[i].weight=ht[s1].weight+ht[s2].weight;
        ht[i].lchild=s1;
        ht[i].rchild=s2; //��i�ĺ��ӽڵ�
        ht[s1].parent=i;
        ht[s2].parent=i; //��s1,s2��˫�׽ڵ�
    }
}

void CrtHuffmanCode(HuffmanTree ht, HuffmanCode hc, int n)
{
	char *cd;
	int i,c,p,start;
	cd=(char*)malloc(n*sizeof(char));  /*������ǰ����Ĺ����ռ�*/
	cd[n-1]='\0';   /*����������λ��ű��룬���ȴ�ű��������*/
	for(i=1;i<=n;i++)  /*��n��Ҷ�ӽ���Ӧ�Ĺ���������*/
	{
		start=n-1;    /*��ʼ��������ʼָ��*/
		c=i;
		p=ht[i].parent;
		while(p!=0) //�ӵײ�Ҷ�����Ƶ���
        {
            --start;
            if(ht[p].lchild==c)
                cd[start]='0'; //���c������
            else
                cd[start]='1';
            c=p;
            p=ht[p].parent; // ������
        }
        hc[i]=(char *)malloc((n-start)*sizeof(char));  /*Ϊ��i���������ռ�*/
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
