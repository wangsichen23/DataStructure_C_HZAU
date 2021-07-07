/*
������������
 ��֪����һ����������������֮���ÿո���ֿ����뽨��һ�����������������������ΪҶ�ڵ㣬����ù��������Ĵ�Ȩ·�����ȡ�

��������ʽ��
 ���������������ĸ�����Ȼ�������Ϊ��������������������������������10��

�������ʽ��
 �����Ӧ��Ȩֵ

���������롿
 5 4 5 6 7 8

�����������
 69
*/
#include <stdio.h>
#include <string.h>

#define N 20
#define M 2*N-1

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
        if(ht[i].weight<=min && ht[i].parent==0)
        {
            min=ht[i].weight;
            flag1=i;
        }
    }
    min=65536;
    for(i=1;i<=n;i++)
    {
        if(ht[i].weight<=min && ht[i].parent==0 && i!=flag1)
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

int main()
{
    int i,n,wpl=0;
    int w[10];
    HuffmanTree ht;

    scanf("%d",&n);
    for(i=1;i<=n;i++)
        scanf("%d",&w[i]);

    CrtHuffmanTree(ht,w,n);

    for(i=1;i<=2*n-1;i++)
        if(ht[i].lchild!=0)
            wpl+=ht[i].weight;
    printf("%d",wpl);

    return 0;
}
